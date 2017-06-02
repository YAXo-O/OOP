#include "buildingdesigner.h"
#include "floor.h"
#include "tunnel.h"
#include "Lift/liftbase.h"

Building *BuildingDesigner::constructBuilding(int floorCount, QWidget *parent) noexcept
{
    BuildingBuilder builder;
    Building *building = builder.getBuilding(parent);


    // И этажи
    for(int i = 0; i < floorCount; i++)
        building->addFloor(builder.getFloor(i));

    // Добавляем шахту с лифтом
    Tunnel *tunnel = builder.getTunnel(builder.getLift());
    building->layout()->addWidget(tunnel);

    // Дабы изменить размеры виджетов в соответствии с layout
    building->show();
    building->hide();

    // Задаём размеры шахты и лифта, исходя из обновлённых размеров этажей
    tunnel->fromFloorHeight(building->getFloorHeight());

    return building;
}