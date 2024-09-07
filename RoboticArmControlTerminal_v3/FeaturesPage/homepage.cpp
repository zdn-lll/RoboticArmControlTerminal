#include "homepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ElaFlowLayout.h"
#include "ElaPushButton.h"
#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaCheckBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaPopularCard.h"
#include <QDesktopServices>
#include "ElaImageCard.h"



HomePage::HomePage(QWidget *parent) : ElaScrollPage(parent)
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("HOME");

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);

    ElaImageCard* backgroundCard = new ElaImageCard(this);
    backgroundCard->setCardImage(QImage(":/Resources/images/105176498_p0.jpg"));

    ElaText* flowLayoutText = new ElaText("实用功能", this);

    // ElaFlowLayout
    ElaPopularCard* homeCard = new ElaPopularCard(this);
    connect(homeCard, &ElaPopularCard::popularCardButtonClicked, this, [=]() {
        QDesktopServices::openUrl(QUrl("https://github.com/zdn-lll"));
    });
    homeCard->setCardPixmap(QPixmap(":/Resources/images/Meaqua_FuFu.jpg"));
    homeCard->setTitle("机械臂控制终端");
    homeCard->setSubTitle("5.0⭐ 实用程序与工具");
    homeCard->setInteractiveTips("免费下载");
    homeCard->setDetailedText("以太之动-机械臂控制终端致力于给用户提供简洁、美观且使用的集成机械臂控制终端");

    ElaPopularCard* homeCard1 = new ElaPopularCard(this);
    connect(homeCard1, &ElaPopularCard::popularCardButtonClicked, this, [=]() { Q_EMIT roboticArmNavigation(); });
    homeCard1->setTitle("Robotic Arm");
    homeCard1->setSubTitle("5.0⭐ 实用程序与工具");
    homeCard1->setCardPixmap(QPixmap(":/Resources/images/control/AnimatedVisualPlayer.png"));
    homeCard1->setInteractiveTips("免费使用");
    homeCard1->setDetailedText("可视化控制机械臂姿态，实时显示机械臂各项参数");
    homeCard1->setCardButtontext("Go");

    ElaPopularCard* homeCard2 = new ElaPopularCard(this);
    connect(homeCard2, &ElaPopularCard::popularCardButtonClicked, this, [=]() { Q_EMIT gyroscopeNavigation(); });
    homeCard2->setTitle("Gyroscope");
    homeCard2->setSubTitle("5.0⭐ 实用程序与工具");
    homeCard2->setCardPixmap(QPixmap(":/Resources/images/control/Canvas.png"));
    homeCard2->setInteractiveTips("免费使用");
    homeCard2->setDetailedText("可视化陀螺仪参数，简化陀螺仪调试过程");
    homeCard2->setCardButtontext("Go");

    ElaPopularCard* homeCard3 = new ElaPopularCard(this);
    connect(homeCard3, &ElaPopularCard::popularCardButtonClicked, this, [=]() { Q_EMIT serialPortAssistantNavigation(); });
    homeCard3->setTitle("Serial Port Assistant");
    homeCard3->setSubTitle("5.0⭐ 实用程序与工具");
    homeCard3->setCardPixmap(QPixmap(":/Resources/images/control/PipsPager.png"));
    homeCard3->setInteractiveTips("免费使用");
    homeCard3->setDetailedText("功能丰富，页面美观的串口调试助手");
    homeCard3->setCardButtontext("Go");

    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    flowLayout->setIsAnimation(true);
    flowLayout->addWidget(homeCard);
    flowLayout->addWidget(homeCard1);
    flowLayout->addWidget(homeCard2);
    flowLayout->addWidget(homeCard3);

    centerVLayout->addWidget(backgroundCard);
    centerVLayout->addWidget(flowLayoutText);
    centerVLayout->addLayout(flowLayout);

    centerVLayout->addStretch();
    centerVLayout->setContentsMargins(0, 0, 10, 0);
    addCentralWidget(centralWidget,true, true, 0);
}

HomePage::~HomePage()
{

}
