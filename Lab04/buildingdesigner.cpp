#include "buildingdesigner.h"
#include "floor.h"

Building *BuildingDesigner::constructBuilding(int floorCount, QWidget *parent) noexcept
{
    BuildingBuilder builder;
    Building *building = builder.getBuilding(parent);

    for(int i = 0; i < floorCount; i++)
        building->addFloor(builder.getFloor(i));

    return building;
}
