#include <QThread>
#include "waitingstate.h"
#include "../liftbase.h"
#include "Lift/LiftStates/eventlist.h"

WaitingState::WaitingState(LiftBase *parent): LiftState(parent), waitingTime(2000)
{
}

void WaitingState::goUp()
{
}

void WaitingState::goDown()
{
}

void WaitingState::openDoors()
{
}

void WaitingState::closeDoors()
{
    QThread::msleep(waitingTime);
    parent->changeState(closeDoorsEvent);
}

int WaitingState::type()
{
    return waitingState;
}
