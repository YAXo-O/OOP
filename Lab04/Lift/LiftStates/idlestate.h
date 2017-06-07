#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "liftstate.h"

const int idleState = 1;

class IdleState : public LiftState
{
public:
    IdleState(LiftBase *parent);
    ~IdleState() = default;

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    int type() override;
};

#endif // IDLESTATE_H
