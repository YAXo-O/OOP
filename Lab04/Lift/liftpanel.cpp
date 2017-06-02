#include <QGridLayout>
#include <QVBoxLayout>
#include "../Button/button.h"
#include "liftpanel.h"

LiftPanel::LiftPanel(int floors, QWidget *parent) : QWidget(parent), lcdNum(nullptr)
{
    const int perCol = 6;

    QVBoxLayout *vertical = new QVBoxLayout;
    QLCDNumber *lcdNum = new QLCDNumber;
    lcdNum->display(0);
    vertical->addWidget(lcdNum);

    QGridLayout *table = new QGridLayout;
    for(int i = 0; i < floors; i++)
    {
        Button *pb = new Button;
        pb->setText(QString::number(i));
        table->addWidget(pb, (floors-i-1)%perCol, (floors-i-1)/perCol);
    }

    vertical->addLayout(table);
    setLayout(vertical);
}

void LiftPanel::updateFloor(int floor) noexcept
{
    if(lcdNum)
        lcdNum->display(floor);
}
