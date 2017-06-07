#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "liftbase.h"
#include "LiftStates/liftstate.h"

class Machine
{
public:
    Machine(LiftBase *parent);
    ~Machine() = default;

    void getState(LiftState *prev, int event);

private:
    LiftBase *parent;
};

#endif // STATEMACHINE_H
