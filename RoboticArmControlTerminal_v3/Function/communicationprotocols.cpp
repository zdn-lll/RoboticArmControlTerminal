#include "communicationprotocols.h"

CommunicationProtocols::CommunicationProtocols() {}

QVector<uint8_t> ExecuteActionCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> frame;
    uint8_t frameHeader = FRAME_HEADER_MASTER; // 0xAA
    uint8_t frameLength = 24; // Fixed as per your structure
    uint8_t packetSource = EXECUTE_ACTION; // 0x00

    // Add the frame header, length, and packet source
    frame.append(frameHeader);
    frame.append(frameLength);
    frame.append(packetSource);

    // Extract time and servo data from input
    uint16_t time = data[0];
    uint8_t time_H = (time >> 8) & 0xFF;
    uint8_t time_L = time & 0xFF;

    frame.append(time_H);
    frame.append(time_L);

    // Add servo data (6 servos)
    for (int i = 1; i < data.size(); i += 2) {
        uint8_t servoId = data[i];
        uint16_t angle = data[i + 1];
        uint8_t angle_H = (angle >> 8) & 0xFF;
        uint8_t angle_L = angle & 0xFF;

        frame.append(servoId);
        frame.append(angle_H);
        frame.append(angle_L);
    }

    // Calculate the checksum
    uint8_t checksum = 0;
    for (uint8_t byte : frame) {
        checksum += byte;
    }
    checksum &= 0xFF;

    // Add checksum to the frame
    frame.append(checksum);

    return frame;
}

QVector<uint8_t> ExecuteActionCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> response;

    // Check if the data length is valid (should be 4 bytes)
    if (data.size() != 4) {
        // Return an empty vector if the data size is incorrect
        return response;
    }

    // Extract components from the data
    uint8_t frameHeader = data[0];
    uint8_t frameLength = data[1];
    uint8_t payload = data[2];
    uint8_t receivedChecksum = data[3];

    // Verify frame header
    if (frameHeader != FRAME_HEADER_SLAVE) {
        // Return an empty vector if the frame header is incorrect
        return response;
    }

    // Verify frame length
    if (frameLength != 4) {
        // Return an empty vector if the frame length is incorrect
        return response;
    }

    // Calculate the checksum
    uint8_t calculatedChecksum = (frameHeader + frameLength + payload) & 0xFF;

    // Verify checksum
    if (calculatedChecksum != receivedChecksum) {
        // Return an empty vector if the checksum is incorrect
        return response;
    }

    // 提取有效载荷
    if (payload != FREE && payload != BUSY) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return response;
    }

    // If all checks pass, add the payload to the response vector
    response.append(payload);

    return response;
}

QVector<uint8_t> ServoAngleCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> packet;

    // 帧头
    packet.append(0xAA);

    // 计算有效载荷部分
    int numberOfServos = (data.size() - 1) / 2; // 假设每个舵机的数据包含：Servo_ID, Angle_H, Angle_L
    int frameLength = 4 + 2 + 1 + numberOfServos * 3; // 帧长 = 4 + 3 + NUMBER_OF_SERVOS * 3
    packet.append(frameLength);

    // 包源
    packet.append(SERVO_ANGLE); // 0x01

    // Time_H 和 Time_L
    int time = data[0];
    packet.append((time >> 8) & 0xFF); // Time_H
    packet.append(time & 0xFF);        // Time_L

    // NUMBER_OF_SERVOS
    packet.append(numberOfServos);

    // 有效载荷部分：Servo ID 和 角度
    for (int i = 1; i < data.size(); i += 3) {
        int servoID = data[i];
        int angle = data[i + 1];

        packet.append(servoID);
        packet.append((angle >> 8) & 0xFF); // Angle_H
        packet.append(angle & 0xFF);        // Angle_L
    }

    // 校验位
    uint8_t checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum += packet[i];
    }
    packet.append(checksum & 0xFF);

    return packet;
}

QVector<uint8_t> ServoAngleCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != FREE && payload != BUSY) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}

QVector<uint8_t> DownloadActionGroupCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> frame;
    uint8_t frameHeader = FRAME_HEADER_MASTER; // 0xAA
    uint8_t frameLength = 25; // Fixed as per your structure
    uint8_t packetSource = DOWNLOAD_ACTION_GROUP; // 0x02

    // Add the frame header, length, and packet source
    frame.append(frameHeader);
    frame.append(frameLength);
    frame.append(packetSource);

    frame.append(data[0]); // 动作组编号

    // Extract time and servo data from input
    uint16_t time = data[1];
    uint8_t time_H = (time >> 8) & 0xFF;
    uint8_t time_L = time & 0xFF;

    frame.append(time_H);
    frame.append(time_L);

    // Add servo data (6 servos)
    for (int i = 2; i < data.size(); i += 2) {
        uint8_t servoId = data[i];
        uint16_t angle = data[i + 1];
        uint8_t angle_H = (angle >> 8) & 0xFF;
        uint8_t angle_L = angle & 0xFF;

        frame.append(servoId);
        frame.append(angle_H);
        frame.append(angle_L);
    }

    // Calculate the checksum
    uint8_t checksum = 0;
    for (uint8_t byte : frame) {
        checksum += byte;
    }
    checksum &= 0xFF;

    // Add checksum to the frame
    frame.append(checksum);

    return frame;
}

QVector<uint8_t> DownloadActionGroupCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != ACK && payload != ERROR) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}

QVector<uint8_t> ErasingActionGroupCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> packet;

    // 帧头
    packet.append(FRAME_HEADER_MASTER);

    // 帧长
    packet.append(5);  // 固定长度5

    // 包源
    packet.append(ERASE_ACTION_GROUP);  // 0x03

    // 有效载荷 - 动作组编号
    if (!data.isEmpty()) {
        packet.append(data[0] & 0xFF);  // 只使用data的第一个元素，表示动作组编号
    } else {
        // 如果没有提供动作组编号，可以根据需要处理，例如返回空包或默认编号
        return QVector<uint8_t>();  // 返回空结果，表示输入无效
    }

    // 校验位
    uint8_t checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum += packet[i];
    }
    packet.append(checksum & 0xFF);  // 添加校验位

    return packet;
}

QVector<uint8_t> ErasingActionGroupCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != ACK && payload != ERROR) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}

QVector<uint8_t> ExecuteToDownloadActionGroupCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> packet;

    // 帧头
    packet.append(FRAME_HEADER_MASTER);

    // 帧长
    packet.append(5);  // 固定长度5

    // 包源
    packet.append(EXECUTE_DOWNLOADED_ACTION_GROUP);  // 0x04

    // 有效载荷 - 动作组编号
    if (!data.isEmpty()) {
        packet.append(data[0] & 0xFF);  // 只使用data的第一个元素，表示动作组编号
    } else {
        // 如果没有提供动作组编号，可以根据需要处理，例如返回空包或默认编号
        return QVector<uint8_t>();  // 返回空结果，表示输入无效
    }

    // 校验位
    uint8_t checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum += packet[i];
    }
    packet.append(checksum & 0xFF);  // 添加校验位

    return packet;
}

QVector<uint8_t> ExecuteToDownloadActionGroupCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != FREE && payload != BUSY) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}

QVector<uint8_t> StopExecutingActionGroupCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> packet;

    // 帧头
    packet.append(FRAME_HEADER_MASTER);

    // 帧长
    packet.append(5);  // 固定长度5

    // 包源
    packet.append(STOP_EXECUTING_ACTION_GROUP);  // 0x05

    // 有效载荷 - 保留
    packet.append(0);

    // 校验位
    uint8_t checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum += packet[i];
    }
    packet.append(checksum & 0xFF);  // 添加校验位

    return packet;
}

QVector<uint8_t> StopExecutingActionGroupCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != ACK && payload != ERROR) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}

QVector<uint8_t> ErasingAllActionGroupCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> packet;

    // 帧头
    packet.append(FRAME_HEADER_MASTER);

    // 帧长
    packet.append(5);  // 固定长度5

    // 包源
    packet.append(ERASE_ALL_ACTION_GROUP);  // 0x06

    // 有效载荷 - 保留
    packet.append(0);

    // 校验位
    uint8_t checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum += packet[i];
    }
    packet.append(checksum & 0xFF);  // 添加校验位

    return packet;
}

QVector<uint8_t> ErasingAllActionGroupCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != ACK && payload != ERROR) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}

QVector<uint8_t> ExecuteToAllDownloadActionGroupCommunicationProtocol::SendToSlave(const QVector<int> &data)
{
    QVector<uint8_t> packet;

    // 帧头
    packet.append(FRAME_HEADER_MASTER);

    // 帧长
    packet.append(5);  // 固定长度5

    // 包源
    packet.append(EXECUTE_ALL_DOWNLOADED_ACTION_GROUP);  // 0x06

    // 有效载荷 - 保留
    packet.append(0);

    // 校验位
    uint8_t checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum += packet[i];
    }
    packet.append(checksum & 0xFF);  // 添加校验位

    return packet;
}

QVector<uint8_t> ExecuteToAllDownloadActionGroupCommunicationProtocol::ReceiveFromSlave(QVector<uint8_t> data)
{
    QVector<uint8_t> result;

    // 检查数据长度是否符合协议要求（至少4个字节）
    if (data.size() < 4) {
        // 返回空结果或一些错误码
        return result;
    }

    // 校验帧头
    if (data[0] != FRAME_HEADER_SLAVE) {
        // 如果帧头不正确，可以返回空结果或错误码
        return result;
    }

    // 校验帧长
    int frameLength = data[1];
    if (frameLength != 4 || data.size() != 4) {
        // 如果帧长不正确或实际数据长度不匹配，可以返回空结果或错误码
        return result;
    }

    // 提取有效载荷
    uint8_t payload = data[2];
    if (payload != FREE && payload != BUSY) {
        // 如果有效载荷值不符合预期，可以返回空结果或错误码
        return result;
    }

    // 校验位校验
    uint8_t checksum = data[3];
    uint8_t calculatedChecksum = (data[0] + data[1] + data[2]) & 0xFF;

    if (checksum != calculatedChecksum) {
        // 如果校验位不正确，可以返回空结果或错误码
        return result;
    }

    // 将有效载荷放入结果中
    result.append(payload);

    return result;
}
