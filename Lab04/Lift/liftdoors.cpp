#include <QPainter>
#include "liftdoors.h"
#include "QDebug"

LiftDoors::LiftDoors(QColor col, QWidget *parent) : QWidget(parent), doorCol(col), doorFill(1.f), preDoorFill(1.f)
{
}

void LiftDoors::setDoor(float doorOpen, float preDoorOpen)
{
    doorFill = doorOpen;
    preDoorFill = preDoorOpen;

    repaint();
}

void LiftDoors::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    float firstWidth = width()/2*preDoorFill;
    QRect door1(0, 0, firstWidth, height());
    QRect door2(firstWidth, 0, width()/2*doorFill + firstWidth, height());
    p.fillRect(door1, doorCol);
    p.fillRect(door2, doorCol.darker(150));

    p.end();
}
