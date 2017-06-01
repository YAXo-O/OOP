#ifndef BUILDINGBUILDER_H
#define BUILDINGBUILDER_H

#include "floor.h"
#include "building.h"

class BuildingBuilder
{
public:
    BuildingBuilder() = default;
    ~BuildingBuilder() = default;

    Floor *getFloor(int floorNum = 0, QColor wallColor = Qt::cyan, QWidget *parent = nullptr) noexcept;
    Building *getBuilding(QWidget *parent = nullptr) noexcept;

};

#endif // BUILDINGBUILDER_H
