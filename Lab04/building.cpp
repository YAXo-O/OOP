#include <QHBoxLayout>
#include <stdexcept>
#include "building.h"

Building::Building(QWidget *parent) : QWidget(parent), floorsLayout(new QVBoxLayout), lift(nullptr), panel(nullptr)
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addLayout(floorsLayout);
    setLayout(horizontalLayout);

}

void Building::addFloor(Floor *f) noexcept
{
    floors.push_back(f);
    floorsLayout->insertWidget(0, f);
}

void Building::removeFloor(int id) throw(std::out_of_range)
{
    if(id >= floors.count() || id < 0)
        throw std::out_of_range("Incorrect floor specified");

    Floor *f = floors[id];
    floorsLayout->removeWidget(f);
    floors.remove(id);
}

void Building::removeFloor(Floor *f) throw(std::out_of_range, std::invalid_argument)
{
    int id = 0;
    bool bSearching = true;
    for(auto i = floors.begin(); i != floors.end() && bSearching; i++, id++)
    {
        if(*i == f)
        {
            bSearching = false;
            removeFloor(id);
        }
    }

    if(bSearching)
        std::invalid_argument("Specified floor is not in this building");
}

void Building::addLift(LiftBase *l) noexcept
{
    lift = l;
    lift->setOwner(this);
}

void Building::addLiftPanel(LiftPanel *p) noexcept
{
    panel = p;
}

void Building::connectLiftToPanel() throw(std::invalid_argument)
{
    if(!lift || !panel)
        throw std::invalid_argument("Both lift and panel should be specified to be connected");

    connect(lift, SIGNAL(floorChanged(int)), panel, SLOT(updateFloor(int)));
}

int Building::getFloorsCount() noexcept
{
    return floors.count();
}

int Building::getFloorHeight() throw(std::out_of_range)
{
    if(floors.empty())
        throw std::out_of_range("No floors currently exist");

    return floors[0]->height();
}

int Building::getLiftFloor(LiftBase *lift) throw(std::out_of_range)
{
    if(!floors.count())
        throw std::out_of_range("No floors are present in the building");

    bool bGoSearching = true;
    int floor = 0;
    for(int i = 0; i < floors.count()-1 && bGoSearching; i++)
    {
        if(floors[i]->y() <= lift->y() && (floors[i]->y() + floors[i]->height()) >= lift->y())
        {
            bGoSearching = false;
            floor = i;
        }
    }

    if(bGoSearching)
        throw std::out_of_range("Lift is out of the building");

    return floor;
}

int Building::getFloorY(int floor) throw (std::out_of_range)
{
    if(floor > floors.count() || floor < 0)
        throw std::out_of_range("non-existing floor y coordinate required!");

    return floors[floor]->y();
}
