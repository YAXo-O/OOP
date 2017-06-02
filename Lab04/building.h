#ifndef BUILDING_H
#define BUILDING_H

#include <QWidget>
#include <QVector>
#include <QVBoxLayout>
#include "floor.h"
#include "Lift/liftbase.h"
#include "Lift/liftpanel.h"

class Building : public QWidget
{
    Q_OBJECT
public:
    explicit Building(QWidget *parent = nullptr);
    ~Building() = default;

    void addFloor(Floor *f) noexcept;
    void removeFloor(int id) throw(std::out_of_range); // Удаляем этаж из здания и освобождаем память
    void removeFloor(Floor *f) throw(std::out_of_range, std::invalid_argument);

    void addLift(LiftBase *l) noexcept;
    void addLiftPanel(LiftPanel *p) noexcept;
    void connectLiftToPanel() throw(std::invalid_argument);

    int getFloorsCount() noexcept;
    int getFloorHeight() throw(std::out_of_range);
    int getLiftFloor(LiftBase *lift) throw(std::out_of_range);

private:
    QVector<Floor *> floors;
    QVBoxLayout *floorsLayout;
    LiftBase *lift;
    LiftPanel *panel;
};

#endif // BUILDING_H
