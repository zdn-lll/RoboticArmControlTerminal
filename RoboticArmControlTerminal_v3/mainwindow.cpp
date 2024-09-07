#include "mainwindow.h"

#include <QDebug>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>

#include "ElaContentDialog.h"
#include "ElaDockWidget.h"
#include "ElaEventBus.h"
#include "ElaGraphicsItem.h"
#include "ElaGraphicsScene.h"
#include "ElaGraphicsView.h"
#include "ElaLog.h"
#include "ElaMenu.h"
#include "ElaMenuBar.h"
#include "ElaProgressBar.h"
#include "ElaStatusBar.h"
#include "ElaText.h"
#include "ElaToolBar.h"
#include "ElaToolButton.h"
#include "ElaWidget.h"

#include "FeaturesPage/about.h"
#include "FeaturesPage/homepage.h"
#include "FeaturesPage/roboticarmpage.h"
#include "FeaturesPage/gyroscopepage.h"
#include "FeaturesPage/serialportassistantpage.h"

MainWindow::MainWindow() {
    initWindow();

    initContent();

    // 拦截默认关闭事件
    this->setIsDefaultClosed(false);
    connect(this, &MainWindow::closeButtonClicked, this, &MainWindow::onCloseButtonClicked);

    //移动到中心
    moveToCenter();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onCloseButtonClicked()
{
    ElaContentDialog* dialog = new ElaContentDialog(this);
    connect(dialog, &ElaContentDialog::rightButtonClicked, this, &MainWindow::closeWindow);
    connect(dialog, &ElaContentDialog::middleButtonClicked, this, &MainWindow::showMinimized);
    dialog->show();
}

void MainWindow::initWindow()
{
    setWindowIcon(QIcon(":/Resources/images/Meaqua_FuFu.jpg"));
    // resize(1200, 740);
    resize(1450, 917);
    setUserInfoCardPixmap(QPixmap(":/Resources/images/Meaqua_FuFu.jpg"));
    setUserInfoCardTitle("Meaqua_FuFu");
    setUserInfoCardSubTitle("1806792066@.com");
    setWindowTitle("机械臂控制终端");
}

void MainWindow::initContent()
{
    _aboutPage = new About();
    _homePage = new HomePage(this);
    _roboticArmPage = new RoboticArmPage(this);
    _gyroscopePage = new GyroscopePage(this);
    _serialPortAssistantPage = new SerialPortAssistantPage(this);

    addPageNode("Home", _homePage, ElaIconType::HouseChimney);
    addPageNode("Robotic Arm", _roboticArmPage, ElaIconType::RobotAstromech);
    addPageNode("Gyroscope", _gyroscopePage, ElaIconType::Microchip);
    addPageNode("Serial Port Assistant", _serialPortAssistantPage, ElaIconType::Link);

    // connect(this, &MainWindow::userInfoCardClicked, this, [=]() { this->navigation(_serialPortAssistantPage->property("ElaPageKey").toString()); });
    // connect(this, &MainWindow::userInfoCardClicked, this, [=]() { this->navigation(_gyroscopePage->property("ElaPageKey").toString()); });
    // connect(this, &MainWindow::userInfoCardClicked, this, [=]() { this->navigation(_roboticArmPage->property("ElaPageKey").toString()); });
    // connect(this, &MainWindow::userInfoCardClicked, this, [=]() { this->navigation(_homePage->property("ElaPageKey").toString()); });

    addFooterNode("About", nullptr, _aboutKey, 0, ElaIconType::User);
    _aboutPage->setWindowModality(Qt::ApplicationModal);
    _aboutPage->hide();
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (_aboutKey == nodeKey)
        {
            _aboutPage->show();
        }
    });
    // addFooterNode("Setting", new QWidget(this), _settingKey, 0, ElaIconType::GearComplex);
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() { this->navigation(_homePage->property("ElaPageKey").toString()); });
    connect(_homePage, &HomePage::gyroscopeNavigation, this, [=]() { this->navigation(_gyroscopePage->property("ElaPageKey").toString()); });
    connect(_homePage, &HomePage::roboticArmNavigation, this, [=]() { this->navigation(_roboticArmPage->property("ElaPageKey").toString()); });
    connect(_homePage, &HomePage::serialPortAssistantNavigation, this, [=]() { this->navigation(_serialPortAssistantPage->property("ElaPageKey").toString()); });
    // connect(_homePage, &T_Home::elaSceneNavigation, this, [=]() { this->navigation(view->property("ElaPageKey").toString()); });
    // connect(_homePage, &T_Home::elaIconNavigation, this, [=]() { this->navigation(_iconPage->property("ElaPageKey").toString()); });
    // connect(_homePage, &T_Home::elaCardNavigation, this, [=]() { this->navigation(_cardPage->property("ElaPageKey").toString()); });
    qDebug() << "已注册的事件列表" << ElaEventBus::getInstance()->getRegisteredEventsName();
}

