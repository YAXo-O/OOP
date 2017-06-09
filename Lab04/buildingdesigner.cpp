#include <QObject>
#include "buildingdesigner.h"
#include "floor.h"
#include "tunnel.h"
#include "Lift/liftbase.h"

Building *BuildingDesigner::constructBuilding(int floorCount, QWidget *parent) noexcept
{
    BuildingBuilder builder;
    Building *building = builder.getBuilding(parent);

    // Добавляем шахту с лифтом
    LiftBase *lift = builder.getLift();
    Tunnel *tunnel = builder.getTunnel(lift);
    building->layout()->addWidget(tunnel);
    LiftPanel *panel = builder.getLiftPanel(floorCount, parent);
    building->addLift(lift);
    building->addLiftPanel(panel);
    building->connectLiftToPanel();
    QObject::connect(panel, SIGNAL(callFloor(int,int)), lift, SLOT(addDestination(int,int)));
    QObject::connect(lift, SIGNAL(floorChanged(int)), panel, SLOT(reachedFloor(int)));
    QObject::connect(lift, SIGNAL(floorChanged(int)), building, SLOT(reachedFloor(int)));

    // И этажи
    for(int i = 1; i <= floorCount; i++)
    {
        Floor *floor = builder.getFloor(i);
        building->addFloor(floor);
        QObject::connect(floor, SIGNAL(callLift(int,int)), lift, SLOT(addDestination(int,int)));
    }

    // Дабы изменить размеры виджетов в соответствии с layout
    building->show();
    building->hide();

    // Задаём размеры шахты и лифта, исходя из обновлённых размеров этажей
    tunnel->fromFloorHeight(building->getFloorHeight());

    return building;
}
