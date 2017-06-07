#ifndef GOUPSTATE_H
#define GOUPSTATE_H

#include "LiftState.h"

const int goingUpState = 5;

class GoUpState : public LiftState
{
public:
    GoUpState(LiftBase *parent);
    ~GoUpState() = default;

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    int type() override;
};

#endif // GOUPSTATE_H
