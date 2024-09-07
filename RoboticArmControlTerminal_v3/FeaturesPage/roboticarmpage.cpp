#include "roboticarmpage.h"

#include <QEventLoop>
#include <QTimer>

void delay(int milliseconds)
{
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, SLOT(quit()));
    loop.exec();
}


#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QElapsedTimer>
#include <QtConcurrent/QtConcurrent>
#include "ElaPushButton.h"
#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaCheckBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaToggleSwitch.h"
#include "ElaScrollPageArea.h"
#include "ElaSlider.h"
#include "ElaToolButton.h"
#include "ElaImageCard.h"
#include "ElaGraphicsScene.h"
#include "ElaGraphicsItem.h"
#include "ElaGraphicsView.h"
#include "ElaPromotionCard.h"
#include "ElaTableView.h"
#include "ElaMessageButton.h"
#include "ElaSpinBox.h"
#include "ElaMultiSelectComboBox.h"

#include "movesettableview.h"
#include "robotarm.h"
#include "communicationprotocols.h"
// #include "ElaToggleButton.h"

RoboticArmPage::RoboticArmPage(QWidget *parent) : ElaScrollPage(parent)
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Robotic Arm");

    QVBoxLayout* LeftVLayout = new QVBoxLayout(this);
    ElaScrollPageArea* LeftUArea = new ElaScrollPageArea(this);
    ElaScrollPageArea* LeftDArea = new ElaScrollPageArea(this);
    ElaScrollPageArea* LeftDDArea = new ElaScrollPageArea(this);
    LeftVLayout->addWidget(LeftUArea);
    LeftVLayout->addWidget(LeftDArea);

    // ElaScrollPageArea* RightArea = new ElaScrollPageArea(this);
    ElaScrollPageArea* RightDArea = new ElaScrollPageArea(this);
    QVBoxLayout* centralVLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* UpCentralHLayout = new QHBoxLayout(this);
    QHBoxLayout* DnCentralHLayout = new QHBoxLayout(this);

    QVBoxLayout* LeftSubUVLayout = new QVBoxLayout(LeftUArea);
    QVBoxLayout* LeftSubDVLayout = new QVBoxLayout(LeftDArea);
    QVBoxLayout* RightVLayout = new QVBoxLayout(this);
    QVBoxLayout* RightDVLayout = new QVBoxLayout(RightDArea);


    /************************** 左侧 **************************/

    /************************** 左上 **************************/

    // 腕侧向关节（Wrist Twist Joint, J6) 夹子
    _ClawToggleSwitch = new ElaToggleSwitch(this);
    // ElaScrollPageArea* toggleSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* clawLayout = new QHBoxLayout(this);
    ElaText* clawText = new ElaText("Claw J6", this);
    clawText->setTextPixelSize(15);
    clawLayout->addWidget(clawText);
    clawLayout->addWidget(_ClawToggleSwitch);

    // 腕旋转关节（Wrist Rotation Joint, J5）
    QVBoxLayout* J5Layout = new QVBoxLayout(this);
    QHBoxLayout* J5UpLayout = new QHBoxLayout(this);
    ElaText* JointNameText5 = new ElaText("腕旋转关节 J5", 15, this);
    _J5_Text = new ElaText("0", 15, this);
    J5UpLayout->addWidget(JointNameText5);
    J5UpLayout->addStretch();
    J5UpLayout->addWidget(_J5_Text);
    _J5_Slider = new ElaSlider(this);
    J5Layout->addLayout(J5UpLayout);
    J5Layout->addWidget(_J5_Slider);

    // 腕弯曲关节（Wrist Bend Joint, J4）
    QVBoxLayout* J4Layout = new QVBoxLayout(this);
    QHBoxLayout* J4UpLayout = new QHBoxLayout(this);
    ElaText* JointNameText4 = new ElaText("腕弯曲关节 J4", 15, this);
    _J4_Text = new ElaText("0", 15, this);
    J4UpLayout->addWidget(JointNameText4);
    J4UpLayout->addStretch();
    J4UpLayout->addWidget(_J4_Text);
    _J4_Slider = new ElaSlider(this);
    J4Layout->addLayout(J4UpLayout);
    J4Layout->addWidget(_J4_Slider);

    // 肘关节（Elbow Joint, J3）
    QVBoxLayout* J3Layout = new QVBoxLayout(this);
    QHBoxLayout* J3UpLayout = new QHBoxLayout(this);
    ElaText* JointNameText3 = new ElaText("肘关节 J3", 15, this);
    _J3_Text = new ElaText("0", 15, this);
    J3UpLayout->addWidget(JointNameText3);
    J3UpLayout->addStretch();
    J3UpLayout->addWidget(_J3_Text);
    _J3_Slider = new ElaSlider(this);
    J3Layout->addLayout(J3UpLayout);
    J3Layout->addWidget(_J3_Slider);

    // 肩关节（Shoulder Joint, J2）
    QVBoxLayout* J2Layout = new QVBoxLayout(this);
    QHBoxLayout* J2UpLayout = new QHBoxLayout(this);
    ElaText* JointNameText2 = new ElaText("肩关节 J2", 15, this);
    _J2_Text = new ElaText("0", 15, this);
    J2UpLayout->addWidget(JointNameText2);
    J2UpLayout->addStretch();
    J2UpLayout->addWidget(_J2_Text);
    _J2_Slider = new ElaSlider(this);
    J2Layout->addLayout(J2UpLayout);
    J2Layout->addWidget(_J2_Slider);

    // 基座旋转关节（Base Rotation Joint, J1）
    QVBoxLayout* J1Layout = new QVBoxLayout(this);
    QHBoxLayout* J1UpLayout = new QHBoxLayout(this);
    ElaText* JointNameText1 = new ElaText("基座旋转关节 J1", 15, this);
    _J1_Text = new ElaText("0", 15, this);
    J1UpLayout->addWidget(JointNameText1);
    J1UpLayout->addStretch();
    J1UpLayout->addWidget(_J1_Text);
    _J1_Slider = new ElaSlider(this);
    J1Layout->addLayout(J1UpLayout);
    J1Layout->addWidget(_J1_Slider);

    /************************** 左上 **************************/

    /************************** 左下 **************************/

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

    // 串口开关
    _pushButton_serial = new ElaPushButton(this);
    _pushButton_serial->setText("打开串口");

    // 执行动作
    _pushButton_Move = new ElaPushButton(this);
    _pushButton_Move->setText("执行动作");

    // 执行时间2
    // ElaText* actionTimeText_2 = new ElaText(this);
    // actionTimeText_2->setText("执行时间(ms):");
    // actionTimeText_2->setTextPixelSize(18);
    // _spinBox_ActionTime_2 = new ElaSpinBox(this);
    // _spinBox_ActionTime_2->setMaximum(65535);
    // _spinBox_ActionTime_2->setMinimum(0);
    // _spinBox_ActionTime_2->setValue(1000);
    // QHBoxLayout* actionTime_2_HBoxLayout = new QHBoxLayout(this);
    // actionTime_2_HBoxLayout->addWidget(actionTimeText_2);
    // actionTime_2_HBoxLayout->addWidget(_spinBox_ActionTime_2);

    // 机械臂复位
    _pushButton_reset = new ElaPushButton(this);
    _pushButton_reset->setText("复位");

    // 自定义舵机参数
    _pushButton_Customize = new ElaPushButton(this);
    _pushButton_Customize->setText("自定义舵机参数");

    // 帮助按钮
    _toolButton_Help = new ElaToolButton(this);
    _toolButton_Help->setElaIcon(ElaIconType::CircleQuestion);

    QHBoxLayout* hLayout_Customize = new QHBoxLayout();
    hLayout_Customize->addWidget(_pushButton_Customize);
    hLayout_Customize->addWidget(_toolButton_Help);

    /************************** 左下 **************************/

    /************************** 左下下 **************************/

    // 下载
    _pushButton_Donwload = new ElaPushButton(this);
    _pushButton_Donwload->setText("下载");

    // 擦除
    _pushButton_Erase = new ElaPushButton(this);
    _pushButton_Erase->setText("擦除动作组");

    // 动作组选项
    _multiSelectComboBox_EraseMoveSet = new ElaMultiSelectComboBox(this);
    _multiSelectComboBox_EraseMoveSet->addItem("ALL");
    QStringList comboList_moveSet;
    for (int i = 0; i < 256; ++i) {
        comboList_moveSet.append(QString::number(i));
    }
    _multiSelectComboBox_EraseMoveSet->addItems(comboList_moveSet);

    connect(_multiSelectComboBox_EraseMoveSet, &ElaMultiSelectComboBox::currentIndexChanged, _multiSelectComboBox_EraseMoveSet, [=](int index){
        auto list = _multiSelectComboBox_EraseMoveSet->getCurrentSelection();
        qDebug() << "activated" << index;

        if(list.size() > 1 && list.first() == "ALL")
        {
            if(list.size() == 2)
            {
                if(index != -1)
                    _multiSelectComboBox_EraseMoveSet->setCurrentSelection(index);
            }
            else
                _multiSelectComboBox_EraseMoveSet->setCurrentSelection(0);
        }
    });

    QHBoxLayout* hLayout_Erase = new QHBoxLayout();
    hLayout_Erase->addWidget(_pushButton_Erase, 1);
    hLayout_Erase->addWidget(_multiSelectComboBox_EraseMoveSet);

    QVBoxLayout* MoveSet_VBoxLayout = new QVBoxLayout(LeftDDArea);
    MoveSet_VBoxLayout->addWidget(_pushButton_Donwload);
    MoveSet_VBoxLayout->addLayout(hLayout_Erase);

    // 动作组编号
    ElaText* moveSetNumberText = new ElaText(this);
    moveSetNumberText->setText("动作组:");
    moveSetNumberText->setTextPixelSize(18);
    _spinBox_MoveSetNumber = new ElaSpinBox(this);
    _spinBox_MoveSetNumber->setMaximum(255);
    _spinBox_MoveSetNumber->setMinimum(0);
    QHBoxLayout* moveSetNumber_HBoxLayout = new QHBoxLayout(this);
    moveSetNumber_HBoxLayout->addWidget(moveSetNumberText);
    moveSetNumber_HBoxLayout->addWidget(_spinBox_MoveSetNumber);

    MoveSet_VBoxLayout->addLayout(moveSetNumber_HBoxLayout);

    // 在线运行
    _pushButton_RunningOnline = new ElaPushButton(this);
    _pushButton_RunningOnline->setText("在线运行");

    // 执行时间
    ElaText* actionTimeText = new ElaText(this);
    actionTimeText->setText("执行时间(ms):");
    actionTimeText->setTextPixelSize(18);
    _spinBox_ActionTime = new ElaSpinBox(this);
    _spinBox_ActionTime->setMaximum(65535);
    _spinBox_ActionTime->setMinimum(0);
    _spinBox_ActionTime->setValue(1000);
    QHBoxLayout* actionTime_HBoxLayout = new QHBoxLayout(this);
    actionTime_HBoxLayout->addWidget(actionTimeText);
    actionTime_HBoxLayout->addWidget(_spinBox_ActionTime);

    // 添加动作
    _pushButton_AddMove = new ElaPushButton(this);
    _pushButton_AddMove->setText("添加动作");

    // 删除动作
    _pushButton_DelMove = new ElaPushButton(this);
    _pushButton_DelMove->setText("删除动作");

    MoveSet_VBoxLayout->addStretch();
    MoveSet_VBoxLayout->addWidget(_pushButton_RunningOnline);
    MoveSet_VBoxLayout->addLayout(actionTime_HBoxLayout);
    MoveSet_VBoxLayout->addWidget(_pushButton_AddMove);
    MoveSet_VBoxLayout->addWidget(_pushButton_DelMove);

    // 执行
    _pushButton_MoveSet_Go = new ElaPushButton(this);
    _pushButton_MoveSet_Go->setText("运行动作组");

    // 动作组选项
    _multiSelectComboBox_MoveSet_Go = new ElaMultiSelectComboBox(this);
    _multiSelectComboBox_MoveSet_Go->addItem("ALL");
    _multiSelectComboBox_MoveSet_Go->addItems(comboList_moveSet);

    connect(_multiSelectComboBox_MoveSet_Go, &ElaMultiSelectComboBox::currentIndexChanged, _multiSelectComboBox_MoveSet_Go, [=](int index){
        auto list = _multiSelectComboBox_MoveSet_Go->getCurrentSelection();
        qDebug() << "activated" << index;

        if(list.size() > 1 && list.first() == "ALL")
        {
            if(list.size() == 2)
            {
                if(index != -1)
                    _multiSelectComboBox_MoveSet_Go->setCurrentSelection(index);
            }
            else
                _multiSelectComboBox_MoveSet_Go->setCurrentSelection(0);
        }
    });

    // 停止
    _pushButton_MoveSet_Stop = new ElaPushButton(this);
    _pushButton_MoveSet_Stop->setText("停止");

    QHBoxLayout* HBoxLayout = new QHBoxLayout(this);
    HBoxLayout->addWidget(_pushButton_MoveSet_Go, 1);
    HBoxLayout->addWidget(_multiSelectComboBox_MoveSet_Go);
    HBoxLayout->addWidget(_pushButton_MoveSet_Stop);
    MoveSet_VBoxLayout->addLayout(HBoxLayout);
    /************************** 左侧 **************************/

    /************************** 右侧 **************************/

    ElaPromotionCard *_promotionCard = new ElaPromotionCard(this);
    QPixmap pixmap(":/Resources/images/RoboticArm2D.png");
    _promotionCard->setCardPixmap(pixmap);

    // 动作组表格
    _moveSetTableView = new ElaTableView(this);
    for (int i = 0; i < 256; ++i) {
        _moveSet[i] = new MoveSetTableView(this);
    }
    QFont tableHeaderFont = _moveSetTableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _moveSetTableView->horizontalHeader()->setFont(tableHeaderFont);
    _moveSetTableView->setModel(_moveSet[0]);
    _moveSetTableView->setAlternatingRowColors(true);
    // _moveSetTableView->verticalHeader()->setHidden(true);
    _moveSetTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _moveSetTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _moveSetTableView->horizontalHeader()->setMinimumSectionSize(60);
    _moveSetTableView->verticalHeader()->setMinimumSectionSize(46);
    _moveSetTableView->setFixedHeight(300);
    // _moveSetTableView->setMaximumViewportSize(QSize(_moveSetTableView->width(), 5 * _moveSetTableView->rowHeight(0)));
    connect(_moveSetTableView, &ElaTableView::tableViewShow, this, [=]() {
        _moveSetTableView->setColumnWidth(0, 100);
        _moveSetTableView->setColumnWidth(1, 100);
        _moveSetTableView->setColumnWidth(2, 100);
        _moveSetTableView->setColumnWidth(3, 100);
        _moveSetTableView->setColumnWidth(4, 100);
        _moveSetTableView->setColumnWidth(5, 100);
        _moveSetTableView->setColumnWidth(6, 100);
        // _moveSetTableView->setColumnWidth(7, 100);
    });

    /************************** 右侧 **************************/


    // 左侧
    // 左上
    LeftSubUVLayout->addLayout(clawLayout);
    LeftSubUVLayout->addLayout(J5Layout);
    LeftSubUVLayout->addLayout(J4Layout);
    LeftSubUVLayout->addLayout(J3Layout);
    LeftSubUVLayout->addLayout(J2Layout);
    LeftSubUVLayout->addLayout(J1Layout);
    // 左下
    LeftSubDVLayout->addLayout(hLayout_port);
    LeftSubDVLayout->addLayout(hLayout_baudRate);
    LeftSubDVLayout->addWidget(_pushButton_serial);
    LeftSubDVLayout->addWidget(_pushButton_Move);
    // LeftSubDVLayout->addLayout(actionTime_2_HBoxLayout);
    LeftSubDVLayout->addWidget(_pushButton_reset);
    LeftSubDVLayout->addStretch();
    LeftSubDVLayout->addLayout(hLayout_Customize);


    // LeftSubVLayout->addStretch();

    // 右侧
    RightVLayout->addWidget(_promotionCard);

    RightDVLayout->addWidget(_moveSetTableView);


    // 上
    UpCentralHLayout->addLayout(LeftVLayout, 0);
    UpCentralHLayout->addLayout(RightVLayout, 1);

    UpCentralHLayout->addStretch();
    UpCentralHLayout->setContentsMargins(0, 0, 10, 0);

    // 下
    DnCentralHLayout->addWidget(LeftDDArea, 0);
    DnCentralHLayout->addWidget(RightDArea, 1);
    DnCentralHLayout->setContentsMargins(0, 0, 10, 0);

    // 合并
    centralVLayout->addLayout(UpCentralHLayout, 1);
    centralVLayout->addLayout(DnCentralHLayout, 0);
    addCentralWidget(centralWidget,true, true, 0);

    RoboticArmInit();
    DebugFuncInit();

}

RoboticArmPage::~RoboticArmPage()
{

}

void RoboticArmPage::RoboticArmInit()
{
    _arm = new RobotArm();
    JointAngle *J6 = new JointAngle(0, 180, 0);
    JointAngle *J5 = new JointAngle(90, 180, 0);
    JointAngle *J4 = new JointAngle(0, 180, 0);
    JointAngle *J3 = new JointAngle(0, 180, 0);
    JointAngle *J2 = new JointAngle(90, 180, 0);
    JointAngle *J1 = new JointAngle(135, 270, 0);
    _arm->addJoint(J1);
    _arm->addJoint(J2);
    _arm->addJoint(J3);
    _arm->addJoint(J4);
    _arm->addJoint(J5);
    _arm->addJoint(J6);

    _J5_Slider->setRange(0, 180);
    _J4_Slider->setRange(0, 180);
    _J3_Slider->setRange(0, 180);
    _J2_Slider->setRange(0, 180);
    _J1_Slider->setRange(0, 270);

    _J5_Slider->setValue(90);
    _J4_Slider->setValue(0);
    _J3_Slider->setValue(0);
    _J2_Slider->setValue(90);
    _J1_Slider->setValue(135);

    _J5_Text->setText("90");
    _J4_Text->setText("0");
    _J3_Text->setText("0");
    _J2_Text->setText("90");
    _J1_Text->setText("135");

    // J1 连接
    connect(_J1_Slider, &ElaSlider::valueChanged, this, [=]() {
        _J1_Text->setText(QString::number(_J1_Slider->value()));
        J1->setTargetAngle((float)_J1_Slider->value());
    });
    connect(J1, &JointAngle::TargetAngleChange, this, [=]() {
        _J1_Slider->setValue(J1->getTargetAngle());
    });

    // J2 连接
    connect(_J2_Slider, &ElaSlider::valueChanged, this, [=]() {
        _J2_Text->setText(QString::number(_J2_Slider->value()));
        J2->setTargetAngle((float)_J2_Slider->value());
    });
    connect(J2, &JointAngle::TargetAngleChange, this, [=]() {
        _J2_Slider->setValue(J2->getTargetAngle());
    });

    // J3 连接
    connect(_J3_Slider, &ElaSlider::valueChanged, this, [=]() {
        _J3_Text->setText(QString::number(_J3_Slider->value()));
        J3->setTargetAngle((float)_J3_Slider->value());
    });
    connect(J3, &JointAngle::TargetAngleChange, this, [=]() {
        _J3_Slider->setValue(J3->getTargetAngle());
    });

    // J4 连接
    connect(_J4_Slider, &ElaSlider::valueChanged, this, [=]() {
        _J4_Text->setText(QString::number(_J4_Slider->value()));
        J4->setTargetAngle((float)_J4_Slider->value());
    });
    connect(J4, &JointAngle::TargetAngleChange, this, [=]() {
        _J4_Slider->setValue(J4->getTargetAngle());
    });

    // J5 连接
    connect(_J5_Slider, &ElaSlider::valueChanged, this, [=]() {
        _J5_Text->setText(QString::number(_J5_Slider->value()));
        J5->setTargetAngle((float)_J5_Slider->value());
    });
    connect(J5, &JointAngle::TargetAngleChange, this, [=]() {
        _J5_Slider->setValue(J5->getTargetAngle());
    });

}

void RoboticArmPage::DebugFuncInit()
{
    // 机械臂复位按键 连接
    connect(_pushButton_reset, &ElaPushButton::clicked, this, [&]() {_arm->resetAllJointsAngle();});

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

    connect(this, &RoboticArmPage::success, _successMessageButton, &ElaMessageButton::click);
    connect(this, &RoboticArmPage::info, _infoMessageButton, &ElaMessageButton::click);
    connect(this, &RoboticArmPage::warning, _warningMessageButton, &ElaMessageButton::click);
    connect(this, &RoboticArmPage::error, _errorMessageButton, &ElaMessageButton::click);

    /* 将系统当前所有可以使用的串口设备添加到comboBox_serialPort中 */
    serialPort = new QSerialPort(this);
    populateSerialPorts();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RoboticArmPage::populateSerialPorts);
    timer->start(1000);

    _context = new CommunicationContext(std::make_unique<ExecuteActionCommunicationProtocol>());

    connect(_pushButton_serial, &ElaPushButton::clicked, this, &RoboticArmPage::onSerialButtonClicked);
    connect(_pushButton_Move, &ElaPushButton::clicked, this, &RoboticArmPage::onMoveButtonClicked);
    connect(_spinBox_MoveSetNumber, &ElaSpinBox::valueChanged, this, [=]() {_moveSetTableView->setModel(_moveSet[_spinBox_MoveSetNumber->value()]);});
    connect(_pushButton_AddMove, &ElaPushButton::clicked, this, &RoboticArmPage::onAddMoveButtonClicked);
    connect(_pushButton_DelMove, &ElaPushButton::clicked, this, &RoboticArmPage::onDelMoveButtonClicked);
    connect(_pushButton_Donwload, &ElaPushButton::clicked, this, &RoboticArmPage::onDonwloadButtonClicked);
    connect(_pushButton_MoveSet_Stop, &ElaPushButton::clicked, this, &RoboticArmPage::onStopButtonClicked);
    connect(_pushButton_Erase, &ElaPushButton::clicked, this, &RoboticArmPage::onEraseButtonClicked);
    connect(_pushButton_MoveSet_Go, &ElaPushButton::clicked, this, &RoboticArmPage::onMoveSetGoButtonClicked);
    connect(_pushButton_RunningOnline, &ElaPushButton::clicked, this, &RoboticArmPage::onRunningOnlineButtonClicked);
}

void RoboticArmPage::populateSerialPorts()
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

bool RoboticArmPage::sendData(const QByteArray &dataToSend)
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
        return false;
    }
    else
    {
        if (serialPort->isOpen()) {
            serialPort->write(dataToSend);
            return true;
        } else {
            _warningMessageButton->setBarText("串口未打开！");
            warning();
            return false;
        }
    }
}

QVector<int> RoboticArmPage::getSelectRow(int index)
{
    QVector<int> rows;
    // 获取选择模型
    QItemSelectionModel *selectionModel = _moveSetTableView->selectionModel();

    // 获取被选中的行的索引
    QModelIndexList selectedIndexes = selectionModel->selectedRows();
    int row = 0;
    int max = _moveSet[index]->getDataListSize();
    // 输出被选中的行号
    for (const QModelIndex &index : selectedIndexes) {
        row = index.row();
        if(row < max)
        {
            qDebug() << "Selected Row:" << index.row();
            rows.append(index.row());
        }
    }
    return rows;
}

QVector<uint8_t> RoboticArmPage::waitForRespond()
{
    const int timeout = 3000; // 设置等待时间，例如3秒
    QElapsedTimer timer;
    timer.start();

    while (timer.elapsed() < timeout)
    {
        if (serialPort->waitForReadyRead(100))
        {
            QByteArray response = readData();
            QVector<uint8_t> responseData(response.begin(), response.end());

            // 直接返回 _context->ReceiveFromSlave(responseData) 的结果
            QVector<uint8_t> respond = _context->ReceiveFromSlave(responseData);

            if (!respond.isEmpty())
            {
                return respond; // 收到应答，返回响应数据
            }
            else
            {
                return {};
            }
        }
    }
    return {}; // 超时未收到应答，返回空的 QVector<uint8_t>
}

void RoboticArmPage::onSerialButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        // 设置串口名
        serialPort->setPortName(_comboBox_port->currentText());

        // 设置串口参数
        serialPort->setBaudRate(_comboBox_baudRate->currentText().toInt());

        // 尝试打开串口
        if(serialPort->open(QIODevice::ReadWrite))
        {
            // 禁用功能
            _comboBox_baudRate->setEnabled(false);
            _comboBox_port->setEnabled(false);
            _pushButton_serial->setText("关闭串口");

            // // 开启接收数据
            // connect(serialPort, &QSerialPort::readyRead, this, &RoboticArmPage::readData);
            _pushButton_serial->setText("关闭串口");
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
        // disconnect(serialPort, &QSerialPort::readyRead, this, &RoboticArmPage::readData);
        // // 恢复功能
        _comboBox_baudRate->setEnabled(true);
        _comboBox_port->setEnabled(true);
        _infoMessageButton->setBarText("连接已断开");
        info();
        _pushButton_serial->setText("打开串口");
    }
}

QByteArray RoboticArmPage::readData()
{
    QByteArray data = serialPort->read(4);  // 读取串口接收到的数据
    qDebug() << "Received data:" << data;     // 使用 qDebug 打印接收到的数据
    return data;
}

void RoboticArmPage::onMoveButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
    }
    else
    {
        _context->SetProtocol(std::make_unique<ServoAngleCommunicationProtocol>());
        // QVector<int> data{1000, 1, 135, 2, 90, 3, 0, 4, 0, 5, 90, 6, 45};
        // QVector<int> angleSet{ 135, 90, 0, 0, 90, 45};
        QVector<int> TargetSet = _arm->getAllTargetAngle();
        QVector<int> CurSet = _arm->getAllCurAngle();
        QVector<int> angleSet;
        for (int i = 0; i < TargetSet.size(); ++i) {
            if(TargetSet[i] != CurSet[i])
            {
                angleSet.append(i+1);
                angleSet.append(TargetSet[i]);
            }
        }
        if(angleSet.isEmpty())
        {
            _infoMessageButton->setBarText("没有角度变换的舵机!");
            info();
            return;
        }

        qDebug() << angleSet;
        QVector<int> data;
        data.append(2000);
        data.append(angleSet);
        qDebug() << data;
        QVector<uint8_t> cmdVector = _context->SendToSlave(data);
        qDebug() << cmdVector;

        // 将 QVector<uint8_t> 转换为 QByteArray
        QByteArray cmd(reinterpret_cast<const char*>(cmdVector.data()), cmdVector.size());
        qDebug() << cmd;

        if(sendData(cmd))
        {
            _successMessageButton->setBarText("指令发送成功!");
            success();
        }
    }
}

void RoboticArmPage::onAddMoveButtonClicked()
{
    QList<int> data;
    int moveSetNum = _spinBox_MoveSetNumber->value();
    data.append(_spinBox_ActionTime->value());
    data.append(_arm->getAllTargetAngle());
    QList<int> indexs = getSelectRow(moveSetNum);
    if(!indexs.isEmpty())
    {
        _moveSet[moveSetNum]->addData(data, indexs.last());
    }
    else {
        _moveSet[moveSetNum]->addData(data, -1);
    }
    _moveSetTableView->update();
}

void RoboticArmPage::onDelMoveButtonClicked()
{
    int moveSetNum = _spinBox_MoveSetNumber->value();
    QList<int> indexs = getSelectRow(moveSetNum);
    if(!indexs.isEmpty())
    {
        for (auto var : indexs) {
            _moveSet[moveSetNum]->delData(var);
        }
    }
    else
    {
        _moveSet[moveSetNum]->delData();
    }
    _moveSetTableView->update();
    _moveSetTableView->clearSelection();
}

// 循环调用才可下载完毕
void RoboticArmPage::onDonwloadButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
        return;
    }

    int index = _spinBox_MoveSetNumber->value();
    int moveSetSize = _moveSet[index]->getDataListSize();
    if (moveSetSize == 0)
    {
        _infoMessageButton->setBarText("该动作组没有动作!");
        info();
        return;
    }

    _context->SetProtocol(std::make_unique<DownloadActionGroupCommunicationProtocol>());
    _successMessageButton->setBarText("开始下载!");
    success();
    _pushButton_serial->setDisabled(true);
    _pushButton_Donwload->setDisabled(true);
    _pushButton_Erase->setDisabled(true);
    _pushButton_MoveSet_Go->setDisabled(true);
    _pushButton_Donwload->setText("正在下载");

    auto task = [=]() {
        for (int t = 0; t < moveSetSize; ++t) {
            QVector<int> data;
            data.append(index);
            QVector<int> AngelSet = _moveSet[index]->getData(t);
            data.append(AngelSet[0]); // 时间
            for (int i = 1; i < AngelSet.size(); ++i) {
                data.append(i);
                data.append(AngelSet[i]);
            }

            qDebug() << data;
            QVector<uint8_t> cmdVector = _context->SendToSlave(data);
            qDebug() << cmdVector;

            // 将 QVector<uint8_t> 转换为 QByteArray
            QByteArray cmd(reinterpret_cast<const char*>(cmdVector.data()), cmdVector.size());
            qDebug() << cmd;

            if (!sendData(cmd))
            {
                _errorMessageButton->setBarText("下载指令发送失败!");
                error();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
                _pushButton_Donwload->setText("下载");
                return;
            }

            // 等待下位机回复ACK
            QVector<uint8_t> respond = waitForRespond();
            if (respond.isEmpty())
            {
                _errorMessageButton->setBarText("等待ACK超时!");
                error();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
                _pushButton_Donwload->setText("下载");
                return;
            }
            else if (respond[0] == ERROR)
            {
                _errorMessageButton->setBarText("下载失败");
                error();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
                _pushButton_Donwload->setText("下载");
                return;
            }
        }

        _successMessageButton->setBarText("下载指令发送成功!");
        success();
        _pushButton_serial->setDisabled(false);
        _pushButton_Donwload->setDisabled(false);
        _pushButton_Erase->setDisabled(false);
        _pushButton_MoveSet_Go->setDisabled(false);
        _pushButton_Donwload->setText("下载");
    };

    QFuture<void> future = QtConcurrent::run(task);
}

void RoboticArmPage::onEraseButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
        return;
    }
    QList<int> indexs = _multiSelectComboBox_EraseMoveSet->getCurrentSelectionIndex();
    if(indexs.isEmpty())
    {
        _warningMessageButton->setBarText("请选择要擦除的动作组");
        warning();
        return;
    }
    else if(indexs[0] == 0)
    {
        _context->SetProtocol(std::make_unique<ErasingAllActionGroupCommunicationProtocol>());
    }
    else
    {
        _context->SetProtocol(std::make_unique<ErasingActionGroupCommunicationProtocol>());
    }
    auto task = [=]() {
        _pushButton_serial->setDisabled(true);
        _pushButton_Donwload->setDisabled(true);
        _pushButton_Erase->setDisabled(true);
        _pushButton_MoveSet_Go->setDisabled(true);
        for (int i = 0; i < indexs.size(); ++i) {
            QVector<uint8_t> cmdVector = _context->SendToSlave({indexs[i] - 1});
            qDebug() << cmdVector;

            // 将 QVector<uint8_t> 转换为 QByteArray
            QByteArray cmd(reinterpret_cast<const char*>(cmdVector.data()), cmdVector.size());
            qDebug() << cmd;
            if (!sendData(cmd))
            {
                _errorMessageButton->setBarText("擦除指令发送失败!");
                error();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
                return;
            }
            else if(i == 0)
            {
                _successMessageButton->setBarText("擦除指令发送成功!");
                success();
            }

            // 等待下位机回复ACK
            QVector<uint8_t> respond = waitForRespond();
            if (respond.isEmpty())
            {
                _errorMessageButton->setBarText("等待ACK超时!");
                error();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
                return;
            }
            else if (respond[0] == ERROR)
            {
                _errorMessageButton->setBarText("擦除失败");
                error();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
                return;
            }
            else if (respond[0] == ACK)
            {
                if(i == 0)
                    _successMessageButton->setBarText("动作组[ALL] 擦除成功");
                else
                    _successMessageButton->setBarText(QString("动作组[%1] 擦除成功!").arg(indexs[i] - 1 ));
                success();
                _pushButton_serial->setDisabled(false);
                _pushButton_Donwload->setDisabled(false);
                _pushButton_Erase->setDisabled(false);
                _pushButton_MoveSet_Go->setDisabled(false);
            }
        }
    };

    QFuture<void> future = QtConcurrent::run(task);

}

void RoboticArmPage::onStopButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
        return;
    }
    else
    {
        stop();
        _context->SetProtocol(std::make_unique<StopExecutingActionGroupCommunicationProtocol>());
        QVector<uint8_t> cmdVector = _context->SendToSlave({});
        qDebug() << cmdVector;

        // 将 QVector<uint8_t> 转换为 QByteArray
        QByteArray cmd(reinterpret_cast<const char*>(cmdVector.data()), cmdVector.size());
        qDebug() << cmd;
        auto task = [=]() {
            if (!sendData(cmd))
            {
                _errorMessageButton->setBarText("停止指令发送失败!");
                error();
                return;
            }
            else
            {
                _successMessageButton->setBarText("停止指令发送成功!");
                success();
            }

            // 等待下位机回复ACK
            QVector<uint8_t> respond = waitForRespond();
            if (respond.isEmpty())
            {
                _errorMessageButton->setBarText("等待ACK超时!");
                error();
                return;
            }
            else if (respond[0] == ERROR)
            {
                _errorMessageButton->setBarText("停止失败");
                error();
                return;
            }
            else if (respond[0] == ACK)
            {
                _successMessageButton->setBarText("机械臂已停止!");
                success();
            }
        };

        QFuture<void> future = QtConcurrent::run(task);
    }
}

void RoboticArmPage::onMoveSetGoButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
        return;
    }
    QList<int> indexs = _multiSelectComboBox_MoveSet_Go->getCurrentSelectionIndex();
    if(indexs.isEmpty())
    {
        _warningMessageButton->setBarText("请选择要执行的动作组");
        warning();
        return;
    }
    else if(indexs[0] == 0)
    {
        _context->SetProtocol(std::make_unique<ExecuteToAllDownloadActionGroupCommunicationProtocol>());
    }
    else
    {
        _context->SetProtocol(std::make_unique<ExecuteToDownloadActionGroupCommunicationProtocol>());
    }
    for (int i = 0; i < indexs.size(); ++i) {
        QVector<uint8_t> cmdVector = _context->SendToSlave({indexs[i] - 1});
        qDebug() << cmdVector;

        // 将 QVector<uint8_t> 转换为 QByteArray
        QByteArray cmd(reinterpret_cast<const char*>(cmdVector.data()), cmdVector.size());
        qDebug() << cmd;
        if (!sendData(cmd))
        {
            _errorMessageButton->setBarText("执行指令发送失败!");
            error();
            return;
        }
    }
    _successMessageButton->setBarText("执行指令发送成功!");
    success();
}

void RoboticArmPage::onRunningOnlineButtonClicked()
{
    if(_pushButton_serial->text() == "打开串口")
    {
        _warningMessageButton->setBarText("串口未连接");
        warning();
        return;
    }

    int index = _spinBox_MoveSetNumber->value();
    int moveSetSize = _moveSet[index]->getDataListSize();
    if (moveSetSize == 0)
    {
        _infoMessageButton->setBarText("该动作组没有动作!");
        info();
        return;
    }

    _context->SetProtocol(std::make_unique<ExecuteActionCommunicationProtocol>());
    for (int i = 0; i < moveSetSize; ++i) {
        QVector<int> data;
        // data.append(index);
        QVector<int> AngelSet = _moveSet[index]->getData(i);
        data.append(AngelSet[0]); // 时间
        for (int i = 1; i < AngelSet.size(); ++i) {
            data.append(i);
            data.append(AngelSet[i]);
        }

        qDebug() << data;
        QVector<uint8_t> cmdVector = _context->SendToSlave(data);
        qDebug() << cmdVector;

        // 将 QVector<uint8_t> 转换为 QByteArray
        QByteArray cmd(reinterpret_cast<const char*>(cmdVector.data()), cmdVector.size());
        qDebug() << cmd;

        if (!sendData(cmd))
        {
            _errorMessageButton->setBarText("在线执行失败!");
            error();
            return;
        }
        delay(AngelSet[0]);
    }
    _successMessageButton->setBarText("在线执行指令发送成功!");
    success();
}

void RoboticArmPage::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        _moveSetTableView->clearSelection();
    }

    // 调用基类的事件处理（非常重要，以确保正常的鼠标事件处理）
    ElaScrollPage::mouseReleaseEvent(event);
}
