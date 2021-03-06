#ifndef CLOSINGSTATE_H
#define CLOSINGSTATE_H

#include "liftstate.h"

const int closingState = 4;

class ClosingState : public LiftState
{
    Q_OBJECT
public:
    ClosingState(LiftBase *parent);
    ~ClosingState(){}

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    int type() override;

private:
    float door;
    float preDoor;
    float doorRate;
    float preDoorRate;
};

#endif // CLOSINGSTATE_H
