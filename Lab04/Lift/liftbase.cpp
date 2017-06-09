#include <QThread>
#include <QPainter>
#include <QHBoxLayout>
#include <QDebug>
#include "liftbase.h"
#include "building.h"
#include "LiftStates/idlestate.h"
#include "statemachine.h"

bool less(const int i, const int j)
{
    return i < j;
}

bool more(const int i, const int j)
{
    return i > j;
}

LiftBase::LiftBase(QColor backColor, QWidget *parent) : QWidget(parent), backWallColor(backColor),
    speedRate(10),
    curState(nullptr), owner(nullptr), bNoTarget(true),
    door(new LiftDoors(Qt::gray, this)), machine(new Machine(this))
{
    IdleState *idle = new IdleState(this);
    connect(idle, SIGNAL(triggeredUp()), machine, SLOT(goUp()));
    connect(idle, SIGNAL(triggeredDown()), machine, SLOT(goDown()));
    connect(idle, SIGNAL(triggered()), machine, SLOT(floorReached()));

    curState = idle;
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

void LiftBase::updateLists() noexcept
{
    int curFloor = getFloor();
    if(target == curFloor)
    {
        if(upperCallsBuilding.count() && target == upperCallsBuilding[0])
            upperCallsBuilding.remove(0);
        if(lowerCallsBuilding.count() && target == lowerCallsBuilding[0])
            lowerCallsBuilding.remove(0);
        if(upperCallsLift.count() && target == upperCallsLift[0])
            upperCallsLift.remove(0);
        if(lowerCallsLift.count() && target == lowerCallsLift[0])
            lowerCallsLift.remove(0);

        chooseTarget();
    }

    workOnList(upperCallsBuilding, lowerCallsBuilding, less, more);
    workOnList(upperCallsLift, lowerCallsLift, less, more);
    workOnList(lowerCallsBuilding, upperCallsBuilding, more, less);
    workOnList(lowerCallsLift, upperCallsLift, more, less);
}

void LiftBase::workOnList(QVector<int> &vector, QVector<int> &opposite,
                          bool (*condition)(const int, const int), bool (*cmp)(const int, const int)) noexcept
{
    for(int i = 0; i < vector.count() && condition(vector[i], target); i++)
    {
            insert(opposite, vector[i], cmp);
            vector.remove(i);
            i--;
    }
}

void LiftBase::chooseTarget() noexcept
{
    bNoTarget = false;

    // Сначала выборка из вызовов лифта - они приоритетнее
    if(upperCallsLift.count() + lowerCallsLift.count())
    {
        if(upperCallsLift.count() == 0 && lowerCallsLift.count() != 0)
            target = lowerCallsLift[0];
        else if(lowerCallsLift.count() == 0 && upperCallsLift.count() != 0)
            target = upperCallsLift[0];
        else
        {
        int curFloor = getFloor();

        if(upperCallsLift[0] - curFloor <= curFloor - lowerCallsLift[0])
            target = upperCallsLift[0];
        else
            target = lowerCallsLift[0];
        }
    }
    // Иначе выборка из вызовов здания
    else if(upperCallsBuilding.count() + lowerCallsBuilding.count())
    {
        if(upperCallsBuilding.count() == 0 && lowerCallsBuilding.count() != 0)
            target = lowerCallsLift[0];
        else if(lowerCallsBuilding.count() == 0 && upperCallsBuilding.count() != 0)
            target = upperCallsBuilding[0];
        else
        {
        int curFloor = getFloor();

        if(upperCallsBuilding[0] - curFloor <= curFloor - lowerCallsBuilding[0])
            target = upperCallsBuilding[0];
        else
            target = lowerCallsBuilding[0];
        }
    }
    else
        bNoTarget = true;

    return;

}

void LiftBase::addDestination(int floor, int status) throw(std::invalid_argument)
{
    if(status != callStatus::statusFloor && status != callStatus::statusPanel)
        throw std::invalid_argument("unknown call status");

    int curFloor = getFloor();
    if(floor > curFloor)
    {
        if(status == callStatus::statusFloor)
            insert(upperCallsBuilding, floor, more);
        else if(status == callStatus::statusPanel)
            insert(upperCallsLift, floor, more);
    }
    else if(floor < curFloor)
    {
        if(status == callStatus::statusFloor)
            insert(lowerCallsBuilding, floor, less);
        else if(status == callStatus::statusPanel)
            insert(lowerCallsLift,floor, less);
    }

    if(bNoTarget)
    {
        bNoTarget = false;
        target = floor;
    }

    if(target > curFloor)
        goUp();
    else if(target < curFloor)
        goDown();
    else
    {
        bNoTarget = true;
        emit floorChanged(curFloor);
        openDoors();
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

    door->move(0, 8);
    door->resize(width(), height()-16);
}

void LiftBase::insert(QVector<int> &list, int value, bool (*cmpr)(const int v1, const int v2))
{
    for(auto i: list)
    {
        if(cmpr(i, value))
        {
            list.insert(i, value);
            break;
        }
    }
}

void LiftBase::moveLift(int floor) noexcept
{
    int path = owner->getFloorY(floor) - y();
    int dir = path/(abs(path));
    int curSpeed = speedRate * dir;
    int cycles = path/curSpeed;
    for(int i = 0; i < cycles; i++)
    {
        move(x(), y() + curSpeed);
        repaint();
        QThread::msleep(33); // Частота кадров = 30
    }
}
