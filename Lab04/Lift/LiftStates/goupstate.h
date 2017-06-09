#ifndef GOUPSTATE_H
#define GOUPSTATE_H

#include "LiftState.h"

const int goingUpState = 5;

class GoUpState : public LiftState
{
    Q_OBJECT
public:
    GoUpState(LiftBase *parent);
    ~GoUpState(){}

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    void moveLift(int dest) noexcept;

    int type() override;

};

#endif // GOUPSTATE_H
