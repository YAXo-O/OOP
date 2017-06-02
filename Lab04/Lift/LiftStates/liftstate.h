#ifndef LIFTSTATE_H
#define LIFTSTATE_H

class LiftBase;

class LiftState
{
public:
    LiftState(LiftBase *parent);

    virtual void goUp();
    virtual void goDown();
    virtual void openDoors();
    virtual void closeDoors();

protected:
    LiftBase *parent;
};

#endif // LIFTSTATE_H
