#include <QGridLayout>
#include <QVBoxLayout>
#include "liftpanel.h"
#include "callinfo.h"

LiftPanel::LiftPanel(int floors, QWidget *parent) : QWidget(parent), lcdNum(nullptr), buttons(nullptr)
{
    const int perCol = 6;

    QVBoxLayout *vertical = new QVBoxLayout;
    lcdNum = new QLCDNumber;
    lcdNum->display(1);
    lcdNum->setFixedSize(250, 80);
    vertical->addWidget(lcdNum);

    QGridLayout *table = new QGridLayout;
    buttons = new Button[floors];
    count = floors;
    for(int i = 0; i < floors; i++)
    {
        buttons[i].setFloor(i+1);
        buttons[i].setText(QString::number(i+1));
        table->addWidget(&buttons[i], (floors-i-1)%perCol, (floors-i-1)/perCol);
        connect(&buttons[i], SIGNAL(activated()), this, SLOT(buttonPressed()));
    }

    vertical->addLayout(table);
    setLayout(vertical);
}

void LiftPanel::updateFloor(int floor) noexcept
{
    if(lcdNum)
        lcdNum->display(floor);
}

void LiftPanel::reachedFloor(int floor) throw(std::out_of_range)
{
    if(floor-1 >= count || floor < 1 )
        throw std::out_of_range("non-existing floor reached");

    buttons[floor-1].reset();
}

void LiftPanel::buttonPressed()
{
   Button *btn = qobject_cast<Button *>(sender());
   int floor = btn->getFloor();

   emit callFloor(floor, callStatus::statusPanel);
}
