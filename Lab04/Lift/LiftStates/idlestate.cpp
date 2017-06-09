#include "../liftbase.h"
#include "idlestate.h"
#include "eventlist.h"

IdleState::IdleState(LiftBase *parent) : LiftState(parent)
{
}

void IdleState::goUp()
{
    emit triggeredUp();
    //parent->changeState(calledUpEvent);
}

void IdleState::goDown()
{
    emit triggeredDown();
    //parent->changeState(calledDownEvent);
}

void IdleState::openDoors()
{
    emit triggered();
    //parent->changeState(calledHereEvent);
}

void IdleState::closeDoors()
{
    // Нельзя закрыть закрытые двери
}

int IdleState::type()
{
    return idleState;
}
