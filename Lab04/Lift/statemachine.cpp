#include "statemachine.h"
#include "LiftStates/idlestate.h"
#include "LiftStates/openningstate.h"
#include "LiftStates/eventlist.h"
#include "LiftStates/waitingstate.h"
#include "LiftStates/closingstate.h"
#include "LiftStates/goupstate.h"

Machine::Machine(LiftBase *_parent): parent(_parent)
{

}

void Machine::getState(LiftState *prev, int event)
{
    if(prev == nullptr)
        return;

    if(prev->type() == idleState && event == calledHereEvent)
    {
        LiftState *newState = new OpenningState(parent);

        delete parent->curState;
        parent->curState = newState;

        parent->openDoors();
    }

    else if(prev->type() == idleState && event == calledUpEvent)
    {
        LiftState *newState = new GoUpState(parent);

        delete parent->curState;
        parent->curState = newState;

        parent->goUp();
    }

    else if(prev->type() == opennigState && event == waitDoorsEvent)
    {
        LiftState *newState = new WaitingState(parent);

        delete parent->curState;
        parent->curState = newState;

        parent->closeDoors();
    }

    else if(prev->type() == waitingState && event == closeDoorsEvent)
    {
        LiftState *newState = new ClosingState(parent);

        delete parent->curState;
        parent->curState = newState;

        parent->closeDoors();
    }

}
