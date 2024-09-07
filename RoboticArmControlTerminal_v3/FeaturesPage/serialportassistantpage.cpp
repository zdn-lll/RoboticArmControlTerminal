#include "serialportassistantpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "ElaPushButton.h"
#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaCheckBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaMessageButton.h"
#include "ElaScrollPageArea.h"
// #include "ElaToggleButton.h"

SerialPortAssistantPage::SerialPortAssistantPage(QWidget *parent)
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Serial Port Assistant");

    QHBoxLayout* centralHLayout = new QHBoxLayout(centralWidget);
    ElaScrollPageArea* comboBoxAreaLU = new ElaScrollPageArea(this);
    ElaScrollPageArea* comboBoxAreaLD = new ElaScrollPageArea(this);
    ElaScrollPageArea* comboBoxRArea = new ElaScrollPageArea(this);
    QVBoxLayout* leftVLayout = new QVBoxLayout(this);
    QVBoxLayout* leftVLayoutU = new QVBoxLayout(comboBoxAreaLU);
    QVBoxLayout* leftVLayoutD = new QVBoxLayout(comboBoxAreaLD);
    QVBoxLayout* rightVLayout = new QVBoxLayout(comboBoxRArea);


    /******************** 左侧 ********************/

    // 端口号
    ElaText* label_port = new ElaText(this);
    label_port->setText("端口号：");
    label_port->setTextPixelSize(20);
    _comboBox_port = new ElaComboBox(this);
    QHBoxLayout* hLayout_port = new QHBoxLayout();
    hLayout_port->addWidget(label_port);
    hLayout_port->addWidget(_comboBox_port);
    // hLayout_port->addStretch();

    // 波特率
    ElaText* label_baudRate = new ElaText(this);
    label_baudRate->setText("波特率：");
    label_baudRate->setTextPixelSize(20);
    _comboBox_baudRate = new ElaComboBox(this);
    QStringList comboList_baudRate{
        "1200",
        "2400",
        "4800",
        "9600",
        "19200",
        "38400",
        "57600",
        "115200"
    };
    _comboBox_baudRate->addItems(comboList_baudRate);
    QHBoxLayout* hLayout_baudRate = new QHBoxLayout();
    hLayout_baudRate->addWidget(label_baudRate);
    hLayout_baudRate->addWidget(_comboBox_baudRate);
    // hLayout_baudRate->addStretch();

    // 数据位
    ElaText* label_dataBits = new ElaText(this);
    label_dataBits->setText("数据位：");
    label_dataBits->setTextPixelSize(20);
    _comboBox_dataBits = new ElaComboBox(this);
    QStringList comboList_dataBits{
        "5",
        "6",
        "7",
        "8"
    };
    _comboBox_dataBits->addItems(comboList_dataBits);
    QHBoxLayout* hLayout_dataBits = new QHBoxLayout();
    hLayout_dataBits->addWidget(label_dataBits);
    hLayout_dataBits->addWidget(_comboBox_dataBits);
    // hLayout_dataBits->addStretch();

    // 校验位
    ElaText* label_parity = new ElaText(this);
    label_parity->setText("校验位：");
    label_parity->setTextPixelSize(20);
    _comboBox_parity = new ElaComboBox(this);
    QStringList comboList_parity{
        "NONE",
        "Even",
        "Odd",
        "Space",
        "Mark"
    };
    _comboBox_parity->addItems(comboList_parity);
    QHBoxLayout* hLayout_parity = new QHBoxLayout();
    hLayout_parity->addWidget(label_parity);
    hLayout_parity->addWidget(_comboBox_parity);
    // hLayout_parity->addStretch();

    // 停止位
    ElaText* label_stopBits = new ElaText(this);
    label_stopBits->setText("停止位：");
    label_stopBits->setTextPixelSize(20);
    _comboBox_stopBits = new ElaComboBox(this);
    QStringList comboList_stopBits{
        "1",
        "2"
    };
    _comboBox_stopBits->addItems(comboList_stopBits);
    QHBoxLayout* hLayout_stopBits = new QHBoxLayout();
    hLayout_stopBits->addWidget(label_stopBits);
    hLayout_stopBits->addWidget(_comboBox_stopBits);
    // hLayout_stopBits->addStretch();

    // 流控位
    ElaText* label_flowControl = new ElaText(this);
    // label_flowControl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    label_flowControl->setText("流控位：");
    label_flowControl->setTextPixelSize(20);
    _comboBox_flowControl = new ElaComboBox(this);
    QStringList comboList_flowControl{
        "NONE",
        "RTS/CTS",
        "XON/XOFF"
    };
    _comboBox_flowControl->addItems(comboList_flowControl);
    QHBoxLayout* hLayout_flowControl = new QHBoxLayout();
    hLayout_flowControl->addWidget(label_flowControl);
    hLayout_flowControl->addWidget(_comboBox_flowControl);
    // hLayout_flowControl->addStretch();

    // 十六进制复选框
    _checkBox_hexSend = new ElaCheckBox(this);
    _checkBox_hexSend->setText("Hex发送");
    _checkBox_hexShow = new ElaCheckBox(this);
    _checkBox_hexShow->setText("Hex显示");
    QHBoxLayout* hLayout_checkBox_hex = new QHBoxLayout();
    hLayout_checkBox_hex->addWidget(_checkBox_hexSend);
    hLayout_checkBox_hex->addWidget(_checkBox_hexShow);
    // hLayout_checkBox_hex->addStretch(); // 确保复选框与其他控件对齐

    // 打开/关闭串口按钮
    _pushButton_serial = new ElaPushButton(this);
    // _pushButton_serial = new ElaToggleButton(this);
    _pushButton_serial->setText("打开串口");
    _pushButton_serial->setFixedHeight(40); // 增加按钮高度

    /******************** 左侧 ********************/

    /******************** 右侧 ********************/

    ElaText* label_recv = new ElaText(this);
    label_recv->setText("接收数据");
    label_recv->setTextPixelSize(20);



    _plainTextEdit_recv = new ElaPlainTextEdit(this);
    _plainTextEdit_recv->setReadOnly(true);

    ElaText* label_send = new ElaText(this);
    label_send->setText("发送数据");
    label_send->setTextPixelSize(20);

    _plainTextEdit_send = new ElaPlainTextEdit(this);

    // 发送数据按钮
    _pushButton_sendData = new ElaPushButton(this);
    _pushButton_sendData->setText("发送数据");
    _pushButton_sendData->setFixedHeight(40); // 增加按钮高度

    // 清空发送区按钮
    _pushButton_clearSend = new ElaPushButton(this);
    _pushButton_clearSend->setText("清空发送区");
    _pushButton_clearSend->setFixedHeight(40); // 增加按钮高度

    // 清空接收区按钮
    _pushButton_clearReceive = new ElaPushButton(this);
    _pushButton_clearReceive->setText("清空接收区");
    _pushButton_clearReceive->setFixedHeight(40); // 增加按钮高度

    QHBoxLayout* hLayout_buttons = new QHBoxLayout();
    hLayout_buttons->addWidget(_pushButton_sendData);
    hLayout_buttons->addWidget(_pushButton_clearSend);
    hLayout_buttons->addWidget(_pushButton_clearReceive);


    /******************** 右侧 ********************/


    // 左侧
    leftVLayoutU->addLayout(hLayout_port);
    leftVLayoutU->addLayout(hLayout_baudRate);
    leftVLayoutU->addLayout(hLayout_dataBits);
    leftVLayoutU->addLayout(hLayout_parity);
    leftVLayoutU->addLayout(hLayout_stopBits);
    leftVLayoutU->addLayout(hLayout_flowControl);

    leftVLayoutD->addLayout(hLayout_checkBox_hex);
    // leftVLayout->addSpacing(300); // 增加复选框和按钮之间的间距
    leftVLayoutD->addStretch();
    leftVLayoutD->addWidget(_pushButton_serial);
    // leftVLayoutD->addSpacing(10); // 增加复选框和按钮之间的间距

    leftVLayout->addWidget(comboBoxAreaLU);
    leftVLayout->addWidget(comboBoxAreaLD);


    // 右侧
    rightVLayout->addWidget(label_recv);
    rightVLayout->addWidget(_plainTextEdit_recv);
    rightVLayout->addWidget(label_send);
    rightVLayout->addWidget(_plainTextEdit_send);
    rightVLayout->addLayout(hLayout_buttons);
    // rightVLayout->addStretch(); // 确保复选框与其他控件对齐
    // rightVLayout->addSpacing(10);

    // 添加右侧的留空
    // QSpacerItem* rightSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);


    // 合并
    centralHLayout->addLayout(leftVLayout, 0);
    centralHLayout->addWidget(comboBoxRArea, 1);
    // centralHLayout->addItem(rightSpacer); // 添加右侧留空

    centralHLayout->addStretch();
    centralHLayout->setContentsMargins(0, 0, 10, 10);
    addCentralWidget(centralWidget,true, true, 0);

    // 消息提示
    _successMessageButton = new ElaMessageButton("Success", this);
    _successMessageButton->setBarTitle("Success");
    _successMessageButton->hide();

    _infoMessageButton = new ElaMessageButton("Info", this);
    _infoMessageButton->setBarTitle("Information");
    _infoMessageButton->setMessageMode(ElaMessageBarType::Information);
    _infoMessageButton->setPositionPolicy(ElaMessageBarType::TopLeft);
    _infoMessageButton->hide();

    _warningMessageButton = new ElaMessageButton("Warning", this);
    _warningMessageButton->setBarTitle("Warning");
    _warningMessageButton->setMessageMode(ElaMessageBarType::Warning);
    _warningMessageButton->setPositionPolicy(ElaMessageBarType::BottomLeft);
    _warningMessageButton->hide();

    _errorMessageButton = new ElaMessageButton("Error", this);
    _errorMessageButton->setBarTitle("Error");
    _errorMessageButton->setMessageMode(ElaMessageBarType::Error);
    _errorMessageButton->setPositionPolicy(ElaMessageBarType::BottomRight);
    _errorMessageButton->hide();

    connect(this, &SerialPortAssistantPage::success, _successMessageButton, &ElaMessageButton::click);
    connect(this, &SerialPortAssistantPage::info, _infoMessageButton, &ElaMessageButton::click);
    connect(this, &SerialPortAssistantPage::warning, _warningMessageButton, &ElaMessageButton::click);
    connect(this, &SerialPortAssistantPage::error, _errorMessageButton, &ElaMessageButton::click);

    connect(_pushButton_serial, &ElaPushButton::clicked, this, &SerialPortAssistantPage::onSerialButtonClicked);
    // connect(_pushButton_serial, &ElaToggleButton::toggled, this, &SerialPortAssistantPage::onSerialButtonClicked);
    connect(_pushButton_sendData, &ElaPushButton::clicked, this, &SerialPortAssistantPage::onSendDataButtonClicked);
    connect(_pushButton_clearSend, &ElaPushButton::clicked, this, &SerialPortAssistantPage::onClearSendButtonClicked);
    connect(_pushButton_clearReceive, &ElaPushButton::clicked, this, &SerialPortAssistantPage::onClearReceiveButtonClicked);

    /* 将系统当前所有可以使用的串口设备添加到comboBox_serialPort中 */
    serialPort = new QSerialPort(this);
    populateSerialPorts();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SerialPortAssistantPage::populateSerialPorts);
    timer->start(1000);
}

void SerialPortAssistantPage::onSerialButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        // 设置串口名
        serialPort->setPortName(_comboBox_port->currentText());

        // 设置串口参数
        serialPort->setBaudRate(_comboBox_baudRate->currentText().toInt());
        serialPort->setDataBits(QSerialPort::DataBits(_comboBox_dataBits->currentText().toInt()));
        serialPort->setParity(QSerialPort::Parity(_comboBox_parity->currentIndex()));
        serialPort->setStopBits(QSerialPort::StopBits(_comboBox_stopBits->currentText().toInt()));
        serialPort->setFlowControl(QSerialPort::FlowControl(_comboBox_flowControl->currentIndex()));

        // 尝试打开串口
        if(serialPort->open(QIODevice::ReadWrite))
        {
            // 禁用功能
            _comboBox_baudRate->setEnabled(false);
            _comboBox_dataBits->setEnabled(false);
            _comboBox_flowControl->setEnabled(false);
            _comboBox_parity->setEnabled(false);
            _comboBox_port->setEnabled(false);
            _comboBox_stopBits->setEnabled(false);
            _pushButton_serial->setText("关闭串口");

            // 开启接收数据
            connect(serialPort, &QSerialPort::readyRead, this, &SerialPortAssistantPage::readData);
            // _pushButton_serial->setText("关闭串口");
            _successMessageButton->setBarText("串口连接成功");
            success();
        }
        else
        {
            // 串口打开失败，显示错误信息
            _errorMessageButton->setBarText("连接失败");
            error();
        }
    }
    else
    {
        // 关闭串口
        serialPort->close();
        disconnect(serialPort, &QSerialPort::readyRead, this, &SerialPortAssistantPage::readData);
        // 恢复功能
        _comboBox_baudRate->setEnabled(true);
        _comboBox_dataBits->setEnabled(true);
        _comboBox_flowControl->setEnabled(true);
        _comboBox_parity->setEnabled(true);
        _comboBox_port->setEnabled(true);
        _comboBox_stopBits->setEnabled(true);
        _infoMessageButton->setBarText("连接已断开");
        info();
        _pushButton_serial->setText("打开串口");
    }

}

void SerialPortAssistantPage::onSendDataButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
    }
    else
    {
        if(_checkBox_hexSend->isChecked())
        {
            QString hexString = _plainTextEdit_send->toPlainText().remove(' '); // 删除可能的空格

            // 使用QRegularExpression替代QRegExp
            QRegularExpression hexMatcher("^[0-9A-Fa-f]+$");
            QRegularExpressionMatch match = hexMatcher.match(hexString);

            if (!match.hasMatch()) {
                _warningMessageButton->setBarText("请输入有效的十六进制字符串！");
                warning();
                return;
            }

            QByteArray dataToSend = QByteArray::fromHex(hexString.toUtf8());

            if (serialPort->isOpen()) {
                serialPort->write(dataToSend);
                // ui->textBrowser_recv->append("发送的数据: " + dataToSend.toHex(' ').toUpper());
            } else {
                _warningMessageButton->setBarText("串口未打开！");
                warning();
            }
        }
        else
        {
            serialPort->write(_plainTextEdit_send->toPlainText().toUtf8());
        }
    }
}

void SerialPortAssistantPage::onClearSendButtonClicked()
{
    _plainTextEdit_send->clear();
}

void SerialPortAssistantPage::onClearReceiveButtonClicked()
{
    _plainTextEdit_recv->clear();
}

void SerialPortAssistantPage::populateSerialPorts()
{
    // 获取所有可用的串口设备
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    if(activatedPort == availablePorts.size())
    {
        return;
    }
    _comboBox_port->clear();  // 清空当前内容
    activatedPort = availablePorts.size();
    QStringList portNames;
    for (const QSerialPortInfo &portInfo : availablePorts) {
        portNames << portInfo.portName();  // 获取串口的名称
    }

    // 将串口名称添加到 ComboBox 中
    _comboBox_port->addItems(portNames);
}

void SerialPortAssistantPage::readData()
{
    QByteArray buf = serialPort->readAll();

    if (!buf.isEmpty())
    {
        QString displayText;

        if (_checkBox_hexShow->isChecked())
        {
            // 以十六进制显示接收到的数据
            displayText = buf.toHex(' ').toUpper();
        }
        else
        {
            // 以文本形式显示接收到的数据
            displayText = QString::fromUtf8(buf);
        }

        // 使用 insertPlainText 插入文本
        _plainTextEdit_recv->insertPlainText(displayText + '\n');

        // 确保插入后的文本可见
        _plainTextEdit_recv->ensureCursorVisible();
    }
}
