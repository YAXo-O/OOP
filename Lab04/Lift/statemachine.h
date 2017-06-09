#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include "liftbase.h"
#include "LiftStates/liftstate.h"

class Machine: public QObject
{
    Q_OBJECT
public:
    explicit Machine(LiftBase *parent, QObject *qparent = 0);
    ~Machine() = default;

public slots:
    void floorReached();
    void goUp();
    void goDown();
    void doorsClosed();
    void doorsOpened();
    void waitingTimerEvent();

private:
    LiftBase *parent;
};

#endif // STATEMACHINE_H
