#include <QHBoxLayout>
#include <stdexcept>
#include "building.h"
#include <iostream>

Building::Building(QWidget *parent) : QWidget(parent), floorsLayout(new QVBoxLayout)
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

int Building::getFloorsCount() noexcept
{
    return floors.count();
}

int Building::getFloorHeight() throw(std::out_of_range)
{
    if(floors.empty())
        throw std::out_of_range("No floors currently exist");

    std::cout << floors[0]->rect().height() << std::endl;
    return floors[0]->height();
}
