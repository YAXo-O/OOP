#ifndef LIFTBASE_H
#define LIFTBASE_H

#include <QWidget>
#include <stdexcept>
#include <QVector>
#include "LiftStates/liftstate.h"
#include "callinfo.h"
#include "liftdoors.h"

class Building;
class Machine;

class LiftBase : public QWidget
{
    friend class OpenningState;
    friend class ClosingState;
    friend class GoUpState;
    friend class GoDownState;
    friend class Machine;

    Q_OBJECT
public:
    explicit LiftBase(QColor backColor = Qt::lightGray, QWidget *parent = nullptr);
    ~LiftBase() = default;

    void setSpeed(unsigned speed) noexcept;
    unsigned getSpeed() noexcept;

    int getFloor() throw(std::out_of_range); // Текущий этаж

    void setOwner(Building *owner) noexcept;
    Building *getOwner() noexcept;

    void updateLists() noexcept;
    void workOnList(QVector<int> &vector, QVector<int> &opposite,
                    bool (*condition)(const int, const int), bool (*cmp)(const int, const int)) noexcept;
    void chooseTarget() noexcept;

public slots:
    void goUp() throw(std::logic_error);
    void goDown() throw(std::logic_error);
    void openDoors() throw(std::logic_error);
    void closeDoors() throw(std::logic_error);
    void addDestination(int floor, int status) throw(std::invalid_argument);

signals:
    void floorChanged(int floor);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor backWallColor;
    unsigned speedRate;
    LiftState *curState;
    Building *owner;

    QVector<int> upperCallsLift;
    QVector<int> upperCallsBuilding;
    QVector<int> lowerCallsLift;
    QVector<int> lowerCallsBuilding;
    int target;
    bool bNoTarget;

    LiftDoors *door;
    Machine *machine;

    void insert(QVector<int> &list, int value, bool (*cmpr)(const int, const int));

private slots:
    void moveLift(int destination) noexcept;
};

#endif // LIFTBASE_H
