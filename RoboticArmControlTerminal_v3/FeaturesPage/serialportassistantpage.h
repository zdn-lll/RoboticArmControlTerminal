#ifndef SERIALPORTASSISTANTPAGE_H
#define SERIALPORTASSISTANTPAGE_H

#include <ElaScrollPage.h>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QRegularExpression>

class ElaComboBox;
class ElaCheckBox;
class ElaPushButton;
class ElaPlainTextEdit;
class ElaMessageButton;
// class ElaToggleButton;
class SerialPortAssistantPage : public ElaScrollPage
{
    Q_OBJECT
public:
    SerialPortAssistantPage(QWidget* parent = nullptr);
    Q_SIGNAL void success(void);
    Q_SIGNAL void info(void);
    Q_SIGNAL void warning(void);
    Q_SIGNAL void error(void);

private slots:
    void onSerialButtonClicked();
    void onSendDataButtonClicked();
    void onClearSendButtonClicked();
    void onClearReceiveButtonClicked();

    void populateSerialPorts();
    void readData();

private:
    ElaComboBox *_comboBox_port{nullptr};
    ElaComboBox *_comboBox_baudRate{nullptr};
    ElaComboBox *_comboBox_dataBits{nullptr};
    ElaComboBox *_comboBox_parity{nullptr};
    ElaComboBox *_comboBox_stopBits{nullptr};
    ElaComboBox *_comboBox_flowControl{nullptr};
    ElaCheckBox *_checkBox_hexSend{nullptr};
    ElaCheckBox *_checkBox_hexShow{nullptr};
    ElaPushButton *_pushButton_serial{nullptr};
    // ElaToggleButton *_pushButton_serial{nullptr};
    ElaPlainTextEdit *_plainTextEdit_recv{nullptr};
    ElaPlainTextEdit *_plainTextEdit_send{nullptr};
    ElaPushButton *_pushButton_sendData{nullptr};
    ElaPushButton *_pushButton_clearSend{nullptr};
    ElaPushButton *_pushButton_clearReceive{nullptr};
    ElaMessageButton *_successMessageButton{nullptr};
    ElaMessageButton *_infoMessageButton{nullptr};
    ElaMessageButton *_warningMessageButton{nullptr};
    ElaMessageButton *_errorMessageButton{nullptr};

    QSerialPort *serialPort{nullptr};

    int activatedPort{0};
};

#endif // SERIALPORTASSISTANTPAGE_H
