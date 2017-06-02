#include <QPainter>
#include <QHBoxLayout>
#include "liftbase.h"
#include "building.h"

LiftBase::LiftBase(QColor backColor, QWidget *parent) : QWidget(parent), backWallColor(backColor),
    curState(new LiftState(this)), owner(nullptr), currentFloor(0)
{
}

void LiftBase::setSpeed(unsigned speed) noexcept
{
    speedRate = speed;
}

unsigned LiftBase::getSpeed() noexcept
{
    return speedRate;
}

int LiftBase::getFloor() throw(std::out_of_range)
{
    if(!owner)
        throw std::out_of_range("Lift doesn't belong to any building");

    return owner->getLiftFloor(this);
}

void LiftBase::setOwner(Building *_owner) noexcept
{
    owner = _owner;
}

Building *LiftBase::getOwner() noexcept
{
    return owner;
}

void LiftBase::goUp() throw(std::logic_error)
{
    if(!curState)
        throw std::logic_error("No state present!");

    curState->goUp();
}

void LiftBase::goDown() throw(std::logic_error)
{
    if(!curState)
        throw std::logic_error("No state present!");

    curState->goDown();
}

void LiftBase::openDoors() throw(std::logic_error)
{
    if(!curState)
        throw std::logic_error("No state present!");

    curState->openDoors();
}

void LiftBase::closeDoors() throw(std::logic_error)
{
    if(!curState)
        throw std::logic_error("No state present!");

    curState->closeDoors();
}

void LiftBase::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(), backWallColor);
    p.setPen(QPen(Qt::darkGray, 8));
    p.drawLine(0, 4, width(), 4);
    p.drawLine(0, height()-4, width(), height()-4);

    p.end();
}
