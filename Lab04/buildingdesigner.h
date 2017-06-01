#ifndef BUIDLINGDESIGNER_H
#define BUIDLINGDESIGNER_H

#include "building.h"
#include "buildingbuilder.h"

class BuildingDesigner
{
public:
    BuildingDesigner() = default;
    ~BuildingDesigner() = default;

    Building *constructBuilding(int floorCount, QWidget *parent = nullptr) noexcept;

};

#endif // BUIDLINGDESIGNER_H
