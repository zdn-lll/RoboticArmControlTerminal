#ifndef ROBOTICARMPAGE_H
#define ROBOTICARMPAGE_H

#include <ElaScrollPage.h>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QRegularExpression>

class ElaToggleSwitch;
class ElaSlider;
class ElaText;
class ElaComboBox;
class ElaPushButton;
class ElaToolButton;
class ElaTableView;
class ElaMessageButton;
class ElaSpinBox;
class ElaMultiSelectComboBox;

class RobotArm;
class CommunicationContext;
class MoveSetTableView;
class RoboticArmPage : public ElaScrollPage
{
    Q_OBJECT
public:
    RoboticArmPage(QWidget* parent = nullptr);
    ~RoboticArmPage();

    void RoboticArmInit(void);
    void DebugFuncInit(void);
    void populateSerialPorts(void);
    bool sendData(const QByteArray &dataToSend);
    QVector<int> getSelectRow(int index);
    QVector<uint8_t> waitForRespond(void);

    Q_SIGNAL void success(void);
    Q_SIGNAL void info(void);
    Q_SIGNAL void warning(void);
    Q_SIGNAL void error(void);
    Q_SIGNAL void recv(QByteArray data);
    Q_SIGNAL void stop(void);

    Q_SLOT void onSerialButtonClicked();
    Q_SLOT QByteArray readData();
    Q_SLOT void onMoveButtonClicked();
    Q_SLOT void onAddMoveButtonClicked();
    Q_SLOT void onDelMoveButtonClicked();
    Q_SLOT void onDonwloadButtonClicked();
    Q_SLOT void onEraseButtonClicked();
    Q_SLOT void onStopButtonClicked();
    Q_SLOT void onMoveSetGoButtonClicked();
    Q_SLOT void onRunningOnlineButtonClicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    ElaToggleSwitch* _ClawToggleSwitch{nullptr};
    ElaSlider* _J5_Slider{nullptr};
    ElaSlider* _J4_Slider{nullptr};
    ElaSlider* _J3_Slider{nullptr};
    ElaSlider* _J2_Slider{nullptr};
    ElaSlider* _J1_Slider{nullptr};
    ElaText* _J5_Text{nullptr};
    ElaText* _J4_Text{nullptr};
    ElaText* _J3_Text{nullptr};
    ElaText* _J2_Text{nullptr};
    ElaText* _J1_Text{nullptr};
    ElaComboBox *_comboBox_port{nullptr};
    ElaComboBox *_comboBox_baudRate{nullptr};
    ElaPushButton *_pushButton_serial{nullptr};
    ElaPushButton *_pushButton_Move{nullptr};
    ElaPushButton* _pushButton_reset{nullptr};
    ElaPushButton* _pushButton_Customize{nullptr};
    ElaToolButton* _toolButton_Help{nullptr};
    ElaPushButton* _pushButton_Donwload{nullptr};
    ElaPushButton* _pushButton_Erase{nullptr};
    ElaMultiSelectComboBox* _multiSelectComboBox_EraseMoveSet{nullptr};
    ElaSpinBox* _spinBox_MoveSetNumber{nullptr};
    ElaPushButton* _pushButton_RunningOnline{nullptr};
    ElaSpinBox* _spinBox_ActionTime{nullptr};
        // ElaSpinBox* _spinBox_ActionTime_2{nullptr};
    ElaPushButton* _pushButton_AddMove{nullptr};
    ElaPushButton* _pushButton_DelMove{nullptr};
    ElaPushButton* _pushButton_MoveSet_Go{nullptr};
    ElaMultiSelectComboBox* _multiSelectComboBox_MoveSet_Go{nullptr};
    ElaPushButton* _pushButton_MoveSet_Stop{nullptr};
    ElaTableView *_moveSetTableView{nullptr};


    ElaMessageButton *_successMessageButton{nullptr};
    ElaMessageButton *_infoMessageButton{nullptr};
    ElaMessageButton *_warningMessageButton{nullptr};
    ElaMessageButton *_errorMessageButton{nullptr};


    RobotArm *_arm{nullptr};
    QSerialPort *serialPort{nullptr};
    MoveSetTableView* _moveSet[256]{nullptr};


    int activatedPort{0};
    CommunicationContext *_context{nullptr};
};

#endif // ROBOTICARMPAGE_H
