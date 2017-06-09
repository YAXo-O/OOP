#include "godownstate.h"
#include "../liftbase.h"
#include "eventlist.h"

GoDownState::GoDownState(LiftBase *parent): LiftState(parent)
{
}

void GoDownState::goUp()
{
}

void GoDownState::goDown()
{
    int curDest = parent->target;
    if(parent->lowerCallsBuilding.count() && parent->lowerCallsBuilding[0] < curDest)
        curDest = parent->lowerCallsBuilding[0];
    if(parent->lowerCallsLift.count() && parent->lowerCallsLift[0] < curDest)
        curDest = parent->lowerCallsLift[0];

    parent->moveLift(curDest);
    parent->updateLists();

    emit triggered();
    //parent->changeState(reachedTarget);
}

void GoDownState::openDoors()
{
}

void GoDownState::closeDoors()
{
}

int GoDownState::type()
{
    return goingDownState;
}
