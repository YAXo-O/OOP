#include "goupstate.h"
#include "../liftbase.h"
#include "eventlist.h"

GoUpState::GoUpState(LiftBase *parent): LiftState(parent)
{
}

void GoUpState::goUp()
{
    int curDest = parent->target;
    if(parent->upperCallsBuilding.count() && parent->upperCallsBuilding[0] < curDest)
        curDest = parent->upperCallsBuilding[0];
    if(parent->upperCallsLift.count() && parent->upperCallsLift[0] < curDest)
        curDest = parent->upperCallsLift[0];

    parent->moveLift(curDest);
    parent->updateLists();

    parent->changeState(reachedTarget);
}

void GoUpState::goDown()
{
}

void GoUpState::openDoors()
{
}

void GoUpState::closeDoors()
{
}

int GoUpState::type()
{
    return goingUpState;
}
