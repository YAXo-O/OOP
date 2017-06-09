#include "statemachine.h"
#include "LiftStates/idlestate.h"
#include "LiftStates/openningstate.h"
#include "LiftStates/eventlist.h"
#include "LiftStates/waitingstate.h"
#include "LiftStates/closingstate.h"
#include "LiftStates/goupstate.h"
#include "LiftStates/godownstate.h"

Machine::Machine(LiftBase *_parent, QObject *qparent): QObject(qparent), parent(_parent)
{
}

void Machine::floorReached()
{
    LiftState *newState = new OpenningState(parent);

    delete parent->curState;
    parent->curState = newState;
    connect(newState, SIGNAL(triggered()), this, SLOT(doorsOpened()));

    parent->openDoors();

}

void Machine::goUp()
{
    LiftState *newState = new GoUpState(parent);

    delete parent->curState;
    parent->curState = newState;
    connect(newState, SIGNAL(triggered()), this, SLOT(floorReached()));

    parent->goUp();
}

void Machine::goDown()
{
    LiftState *newState = new GoDownState(parent);

    delete parent->curState;
    parent->curState = newState;
    connect(newState, SIGNAL(triggered()), this, SLOT(floorReached()));

    parent->goDown();
}

void Machine::doorsClosed()
{
    IdleState *newState = new IdleState(parent);

    delete parent->curState;
    parent->curState = newState;

    connect(newState, SIGNAL(triggeredUp()), this, SLOT(goUp()));
    connect(newState, SIGNAL(triggeredDown()), this, SLOT(goDown()));
    connect(newState, SIGNAL(triggered()), this, SLOT(floorReached()));

}

void Machine::doorsOpened()
{
    LiftState *newState = new WaitingState(parent);

    delete parent->curState;
    parent->curState = newState;
    connect(newState, SIGNAL(triggered()), this, SLOT(waitingTimerEvent()));

    parent->closeDoors();
}

void Machine::waitingTimerEvent()
{
    LiftState *newState = new ClosingState(parent);

    delete parent->curState;
    parent->curState = newState;
    connect(newState, SIGNAL(triggered()), this, SLOT(doorsClosed()));

    parent->closeDoors();
}
