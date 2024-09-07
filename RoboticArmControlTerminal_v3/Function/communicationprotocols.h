#ifndef COMMUNICATIONPROTOCOLS_H
#define COMMUNICATIONPROTOCOLS_H

#include <QObject>
#include <QVector>

#define FRAME_HEADER_MASTER 0xAA
#define FRAME_HEADER_SLAVE 0xCC

enum PACKAGE_SOURCE_MASTER{
    EXECUTE_ACTION = 0x00,
    SERVO_ANGLE,
    DOWNLOAD_ACTION_GROUP,
    ERASE_ACTION_GROUP,
    EXECUTE_DOWNLOADED_ACTION_GROUP,
    STOP_EXECUTING_ACTION_GROUP,
    ERASE_ALL_ACTION_GROUP,
    EXECUTE_ALL_DOWNLOADED_ACTION_GROUP,
    _SUM_PACKAGE_SOURCE_MASTER
};

enum PACKAGE_SOURCE_SLAVE{
    ACK = 0x00,
    ERROR,
    FREE,
    BUSY,
    _SUM_PACKAGE_SOURCE_SLAVE
};

// 抽象通信接口类
class CommunicationProtocols
{
public:
    CommunicationProtocols();
    virtual ~CommunicationProtocols() = default;

    // 上位机向下位机发送数据
    virtual QVector<uint8_t> SendToSlave(const QVector<int>& data) = 0;

    // 接收解析到的数据
    virtual QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) = 0;
};

/* ↓ ↓ ↓ ↓ 具体通信协议的实现 ↓ ↓ ↓ ↓ */

// 默认

/* 在线执行动作组中的某一个动作 */
class ExecuteActionCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 将目标角度与当前角度不同的舵机转动到目标角度 */
class ServoAngleCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 下载动作组 */
class DownloadActionGroupCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 擦除动作组 */
class ErasingActionGroupCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 执行某一下载的动作组 */
class ExecuteToDownloadActionGroupCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 停止执行动作组 */
class StopExecutingActionGroupCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 擦除全部已下载动作组 */
class ErasingAllActionGroupCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

/* 执行全部已下载动作组 */
class ExecuteToAllDownloadActionGroupCommunicationProtocol : public CommunicationProtocols
{
public:
    QVector<uint8_t> SendToSlave(const QVector<int>& data) override;

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) override;
};

// 自定义

/* ↑ ↑ ↑ ↑ 具体通信协议的实现 ↑ ↑ ↑ ↑ */

// 策略模式
class CommunicationContext {
private:
    std::unique_ptr<CommunicationProtocols> protocol;

public:
    CommunicationContext(std::unique_ptr<CommunicationProtocols> protocol)
        : protocol(std::move(protocol)) {}

    void SetProtocol(std::unique_ptr<CommunicationProtocols> newProtocol) {
        protocol = std::move(newProtocol);
    }

    QVector<uint8_t> SendToSlave(const QVector<int>& data) {
        return protocol->SendToSlave(data);
    }

    QVector<uint8_t> ReceiveFromSlave(QVector<uint8_t> data) {
        return protocol->ReceiveFromSlave(data);
    }
};

#endif // COMMUNICATIONPROTOCOLS_H
