#include <QGridLayout>
#include <QPushButton>
#include "liftpanel.h"

LiftPanel::LiftPanel(int floors, QWidget *parent) : QWidget(parent)
{
    const int perCol = 6;

    QGridLayout *table = new QGridLayout;
    for(int i = 0; i < floors; i++)
    {
        QPushButton *pb = new QPushButton;
        pb->setText(QString::number(i));
        table->addWidget(pb, (floors-i-1)%perCol, (floors-i-1)/perCol);
    }

    setLayout(table);
}
