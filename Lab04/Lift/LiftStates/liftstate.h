#ifndef LIFTSTATE_H
#define LIFTSTATE_H

#include <QObject>

class LiftBase;

class LiftState: public QObject
{
    Q_OBJECT
public:
    LiftState(LiftBase *parent);
    virtual ~LiftState(){}

    virtual void goUp();
    virtual void goDown();
    virtual void openDoors();
    virtual void closeDoors();

    virtual int type() = 0; // Задаёт тип текущего состояния

    LiftBase *getParent();

signals:
    void triggered();

protected:
    LiftBase *parent;
};

#endif // LIFTSTATE_H
