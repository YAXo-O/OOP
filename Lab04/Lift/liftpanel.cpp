#include <QGridLayout>
#include "../Button/button.h"
#include "liftpanel.h"

LiftPanel::LiftPanel(int floors, QWidget *parent) : QWidget(parent)
{
    const int perCol = 6;

    QGridLayout *table = new QGridLayout;
    for(int i = 0; i < floors; i++)
    {
        Button *pb = new Button;
        pb->setText(QString::number(i));
        table->addWidget(pb, (floors-i-1)%perCol, (floors-i-1)/perCol);
    }

    setLayout(table);
}
