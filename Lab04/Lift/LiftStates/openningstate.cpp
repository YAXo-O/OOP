#include <QThread>
#include "../liftbase.h"
#include "openningstate.h"
#include "Lift/LiftStates/eventlist.h"

OpenningState::OpenningState(LiftBase *parent): LiftState(parent), door(1.f), preDoor(1.f),
    doorRate(.05f), preDoorRate(.05f)
{
}

void OpenningState::goUp()
{
}

void OpenningState::goDown()
{
}

void OpenningState::openDoors()
{
    while(door >= 0 && preDoor >= 0)
    {
        parent->door->setDoor(door, preDoor);
        door -= doorRate;
        preDoor -= preDoorRate;

        QThread::msleep(33);
    }

    parent->changeState(waitDoorsEvent);
}

void OpenningState::closeDoors()
{
}

int OpenningState::type()
{
    return opennigState;
}
