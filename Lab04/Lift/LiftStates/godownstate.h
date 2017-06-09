#ifndef GODOWNSTATE_H
#define GODOWNSTATE_H

#include "liftstate.h"

const int goingDownState = 6;

class GoDownState: public LiftState
{
public:
    GoDownState(LiftBase *parent);
    ~GoDownState() = default;

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    int type() override;
};

#endif // GODOWNSTATE_H
