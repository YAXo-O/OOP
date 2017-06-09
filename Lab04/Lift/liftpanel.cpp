#include <QGridLayout>
#include <QVBoxLayout>
#include "../Button/button.h"
#include "liftpanel.h"
#include "callinfo.h"

LiftPanel::LiftPanel(int floors, QWidget *parent) : QWidget(parent), lcdNum(nullptr)
{
    const int perCol = 6;

    QVBoxLayout *vertical = new QVBoxLayout;
    QLCDNumber *lcdNum = new QLCDNumber;
    lcdNum->display(0);
    vertical->addWidget(lcdNum);

    QGridLayout *table = new QGridLayout;
    for(int i = 1; i <= floors; i++)
    {
        Button *pb = new Button(i);
        pb->setText(QString::number(i));
        table->addWidget(pb, (floors-i)%perCol, (floors-i)/perCol);
        connect(pb, SIGNAL(activated()), this, SLOT(buttonPressed()));
    }

    vertical->addLayout(table);
    setLayout(vertical);
}

void LiftPanel::updateFloor(int floor) noexcept
{
    if(lcdNum)
        lcdNum->display(floor);
}

void LiftPanel::buttonPressed()
{
   Button *btn = qobject_cast<Button *>(sender());
   int floor = btn->getFloor();

   emit callFloor(floor, callStatus::statusPanel);
}
