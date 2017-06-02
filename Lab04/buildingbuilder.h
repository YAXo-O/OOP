#ifndef BUILDINGBUILDER_H
#define BUILDINGBUILDER_H

#include "floor.h"
#include "building.h"
#include "Lift/liftbase.h"
#include "tunnel.h"

class BuildingBuilder
{
public:
    BuildingBuilder() = default;
    ~BuildingBuilder() = default;

    Floor *getFloor(int floorNum = 0, QColor wallColor = Qt::cyan, QWidget *parent = nullptr) noexcept;
    LiftBase *getLift(QColor backColor = Qt::lightGray, QWidget *parent = nullptr) noexcept;
    Tunnel *getTunnel(LiftBase *lift, QColor bgColor = QColor(100, 100, 100), QWidget *parent = nullptr) noexcept;
    Building *getBuilding(QWidget *parent = nullptr) noexcept;
};

#endif // BUILDINGBUILDER_H
