#include "buildingbuilder.h"

Floor *BuildingBuilder::getFloor(int floorNum, QColor wallColor, QWidget *parent) noexcept
{
    return new Floor(floorNum, wallColor, parent);
}

LiftBase *BuildingBuilder::getLift(QColor backColor, QWidget *parent) noexcept
{
    return new LiftBase(backColor, parent);
}

Tunnel *BuildingBuilder::getTunnel(LiftBase *lift, QColor bgColor, QWidget *parent) noexcept
{
    return new Tunnel(lift, bgColor, parent);
}

Building *BuildingBuilder::getBuilding(QWidget *parent) noexcept
{
    return new Building(parent);
}
