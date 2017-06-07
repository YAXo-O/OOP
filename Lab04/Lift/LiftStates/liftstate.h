#ifndef LIFTSTATE_H
#define LIFTSTATE_H

class LiftBase;

class LiftState
{
public:
    LiftState(LiftBase *parent);
    ~LiftState() = default;

    virtual void goUp();
    virtual void goDown();
    virtual void openDoors();
    virtual void closeDoors();

    virtual int type() = 0; // Задаёт тип текущего состояния

protected:
    LiftBase *parent;
};

#endif // LIFTSTATE_H
