#include <QThread>
#include "Lift/LiftStates/eventlist.h"
#include "closingstate.h"
#include "Lift/liftbase.h"

ClosingState::ClosingState(LiftBase *parent): LiftState(parent),
    door(0), preDoor(0), doorRate(.05f), preDoorRate(.05f)
{

}

void ClosingState::goUp()
{
}

void ClosingState::goDown()
{
}

void ClosingState::openDoors()
{
}

void ClosingState::closeDoors()
{
    while(door <= 1 && preDoor <= 1)
    {
        parent->door->setDoor(door, preDoor);
        door += doorRate;
        preDoor += preDoorRate;

        QThread::msleep(33);
    }

    emit triggered();
    //parent->changeState(goEvent);
}

int ClosingState::type()
{
    return closingState;
}
