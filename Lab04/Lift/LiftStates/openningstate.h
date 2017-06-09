#ifndef OPENNINGSTATE_H
#define OPENNINGSTATE_H

#include <QTimer>
#include "idlestate.h"

const int opennigState = 2;

class OpenningState : public LiftState
{
    Q_OBJECT
public:
    OpenningState(LiftBase *parent);
    ~OpenningState(){}

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

#endif // OPENNINGSTATE_H
