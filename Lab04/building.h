#ifndef BUILDING_H
#define BUILDING_H

#include <QWidget>
#include <QVector>
#include <QVBoxLayout>
#include "floor.h"

class Building : public QWidget
{
    Q_OBJECT
public:
    explicit Building(QWidget *parent = nullptr);
    ~Building() = default;

    void addFloor(Floor *f) noexcept;
    void removeFloor(int id) throw(std::out_of_range); // Удаляем этаж из здания и освобождаем память
    void removeFloor(Floor *f) throw(std::out_of_range, std::invalid_argument);

    int getFloorsCount() noexcept;
    int getFloorHeight() throw(std::out_of_range);

private:
    QVector<Floor *> floors;
    QVBoxLayout *floorsLayout;
};

#endif // BUILDING_H
