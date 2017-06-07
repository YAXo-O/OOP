#include "../liftbase.h"
#include "idlestate.h"
#include "eventlist.h"

IdleState::IdleState(LiftBase *parent) : LiftState(parent)
{
}

void IdleState::goUp()
{
    parent->changeState(calledUpEvent);
}

void IdleState::goDown()
{
    parent->changeState(calledDownEvent);
}

void IdleState::openDoors()
{
    parent->changeState(calledHereEvent);
}

void IdleState::closeDoors()
{
    // Нельзя закрыть закрытые двери
}

int IdleState::type()
{
    return idleState;
}
