#include <QHBoxLayout>
#include <QPainter>
#include "floor.h"

const QString Floor::floorSignPrefix = "Current floor: ";

Floor::Floor(int _floorNum, QColor _wallColor, QWidget *parent) : QWidget(parent),
    floorNum(_floorNum), callPB(new QPushButton()), wallColor(_wallColor), floorLab(new QLabel)
{
    setLayout(new QHBoxLayout());
    layout()->addWidget(callPB);
    layout()->addWidget(floorLab);

    callPB->setText("Call lift");
    floorLab->setText(floorSignPrefix + QString::number(floorNum));
}

void Floor::changeFloor(int newNum) noexcept
{
    floorNum = newNum;
    floorLab->setText(floorSignPrefix + QString::number(floorNum));
}

void Floor::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(), wallColor); // Зальём фон
    p.setPen(QPen(Qt::darkGray, 8)); // И сделаем окантовочку
    p.drawRect(rect());

    p.end();
}
