#include "liftstate.h"

LiftState::LiftState(LiftBase *_parent): QObject(nullptr), parent(_parent)
{
}

void LiftState::goUp()
{
}

void LiftState::goDown()
{
}

void LiftState::openDoors()
{
}

void LiftState::closeDoors()
{
}

LiftBase *LiftState::getParent()
{
    return parent;
}
