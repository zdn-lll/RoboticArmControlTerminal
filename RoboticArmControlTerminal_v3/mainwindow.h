#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ElaWindow.h>

class About;
class HomePage;
class RoboticArmPage;
class GyroscopePage;
class SerialPortAssistantPage;
class MainWindow : public ElaWindow
{
public:
    MainWindow();
    ~MainWindow();
    Q_SLOT void onCloseButtonClicked();

    void initWindow(void);
    void initContent(void);

private:
    About* _aboutPage{nullptr};
    HomePage* _homePage{nullptr};
    RoboticArmPage* _roboticArmPage{nullptr};
    GyroscopePage* _gyroscopePage{nullptr};
    SerialPortAssistantPage* _serialPortAssistantPage{nullptr};
    QString _elaDxgiKey{""};
    QString _aboutKey{""};
    QString _settingKey{""};
};

#endif // MAINWINDOW_H
