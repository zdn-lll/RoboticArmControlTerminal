#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <ElaScrollPage.h>

class HomePage : public ElaScrollPage
{
    Q_OBJECT
public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();
    Q_SIGNAL void roboticArmNavigation();
    Q_SIGNAL void gyroscopeNavigation();
    Q_SIGNAL void serialPortAssistantNavigation();

};

#endif // HOMEPAGE_H
