#ifndef WAITINGSTATE_H
#define WAITINGSTATE_H

#include "LiftState.h"

const int waitingState = 3;

class WaitingState : public LiftState
{
    Q_OBJECT
public:
    WaitingState(LiftBase *parent);
    ~WaitingState(){}

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    int type() override;


private:
    unsigned long waitingTime;
};

#endif // WAITINGSTATE_H
