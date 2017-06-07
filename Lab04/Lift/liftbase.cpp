#include <QThread>
#include <QPainter>
#include <QHBoxLayout>
#include "liftbase.h"
#include "building.h"

LiftBase::LiftBase(QColor backColor, QWidget *parent) : QWidget(parent), backWallColor(backColor),
    curState(new LiftState(this)), owner(nullptr), bNoTarget(true)
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

void LiftBase::addDestination(int floor, int status) throw(std::invalid_argument)
{
    if(status != callStatus::statusFloor && status != callStatus::statusPanel)
        throw std::invalid_argument("unknown call status");

    int curFloor = getFloor();
    if(floor > curFloor)
    {
        if(status == callStatus::statusFloor)
            upperCallsBuilding.append(floor);
        else if(status == callStatus::statusPanel)
            upperCallsLift.append(floor);
    }
    else if(floor < curFloor)
    {
        if(status == callStatus::statusFloor)
            lowerCallsBuilding.append(floor);
        else if(status == callStatus::statusPanel)
            lowerCallsLift.append(floor);
    }

    // TODO: add situation when lift is on calling floor
    if(bNoTarget)
    {
        bNoTarget = false;
        target = floor;
    }

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

void LiftBase::moveLift(int destination)
{
    int path = destination - y();
    int dir = path/(abs(path));
    int curSpeed = speedRate * dir;
    int cycles = path/curSpeed;
    for(int i = 0; i < cycles; i++)
    {
        move(x(), y() + curSpeed);
        QThread::msleep(33); // Частота кадров = 30
    }
}
