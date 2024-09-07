#include "about.h"
#include "ElaIcon.h"
#include "ElaScrollPage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <ElaText.h>
#include <QDebug>

About::About()
{
    ElaIcon icon;
    ElaScrollPage page;

    setWindowIcon(icon.getElaIcon(ElaIconType::User));
    resize(1200, 740);
    setWindowTitle("About");

    setMinimumSize(200, 280);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->setContentsMargins(5, 10, 5, 5);
    mainLayout->setSpacing(4);
    ElaText* updateTitle = new ElaText("About", 40, this);
    ElaText* update1 = new ElaText("作者：Zhang DingNian", 13, this);
    ElaText* update2 = new ElaText("邮箱：180679206@qq.com", 13, this);
    ElaText* update3 = new ElaText("感谢您的使用", 30, this);
    update1->setIsWrapAnywhere(true);
    update2->setIsWrapAnywhere(true);
    update3->setIsWrapAnywhere(true);

    mainLayout->addWidget(updateTitle);
    mainLayout->addWidget(update1);
    mainLayout->addWidget(update2);
    mainLayout->addWidget(update3);
    mainLayout->addStretch();
}
