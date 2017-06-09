#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "liftstate.h"

const int idleState = 1;

class IdleState : public LiftState
{
    Q_OBJECT
public:
    IdleState(LiftBase *parent);
    ~IdleState(){}

    void goUp() override;
    void goDown() override;
    void openDoors() override;
    void closeDoors() override;

    int type() override;

signals:
    void triggeredDown();
    void triggeredUp();
};

#endif // IDLESTATE_H
