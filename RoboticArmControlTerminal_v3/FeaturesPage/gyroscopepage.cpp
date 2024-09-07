#include "gyroscopepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ElaPushButton.h"
#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaCheckBox.h"
#include "ElaPlainTextEdit.h"

GyroscopePage::GyroscopePage(QWidget *parent)  : ElaScrollPage(parent)
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Gyroscope");

    QHBoxLayout* centralHLayout = new QHBoxLayout(centralWidget);

    centralHLayout->addStretch();
    centralHLayout->setContentsMargins(0, 0, 0, 0);
    addCentralWidget(centralWidget,true, true, 0);
}

GyroscopePage::~GyroscopePage()
{

}
