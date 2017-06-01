#include "buildingbuilder.h"

Floor *BuildingBuilder::getFloor(int floorNum, QColor wallColor, QWidget *parent) noexcept
{
    return new Floor(floorNum, wallColor, parent);
}

Building *BuildingBuilder::getBuilding(QWidget *parent) noexcept
{
    return new Building(parent);
}
