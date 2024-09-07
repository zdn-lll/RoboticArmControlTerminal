#ifndef GYROSCOPEPAGE_H
#define GYROSCOPEPAGE_H

#include <ElaScrollPage.h>

class GyroscopePage : public ElaScrollPage
{
    Q_OBJECT
public:
    GyroscopePage(QWidget* parent = nullptr);
    ~GyroscopePage();
};

#endif // GYROSCOPEPAGE_H
