#ifndef LIFTBASE_H
#define LIFTBASE_H

#include <QWidget>
#include <stdexcept>
#include "LiftStates/liftstate.h"

class Building;

class LiftBase : public QWidget
{
    friend class LiftState;

    Q_OBJECT
public:
    explicit LiftBase(QColor backColor = Qt::lightGray, QWidget *parent = nullptr);
    ~LiftBase() = default;

    void setSpeed(unsigned speed) noexcept;
    unsigned getSpeed() noexcept;
    int getFloor() throw(std::out_of_range);
    void setOwner(Building *owner) noexcept;
    Building *getOwner() noexcept;

public slots:
    void goUp() throw(std::logic_error);
    void goDown() throw(std::logic_error);
    void openDoors() throw(std::logic_error);
    void closeDoors() throw(std::logic_error);

signals:
    void floorChanged(int floor);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor backWallColor;
    unsigned speedRate;
    LiftState *curState;
    Building *owner;
    int currentFloor;

private slots:
    void moveLift(int destination);
};

#endif // LIFTBASE_H
