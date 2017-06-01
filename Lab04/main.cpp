#include <QApplication>
#include "buildingdesigner.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;

    BuildingDesigner designer;
    Building *building = designer.constructBuilding(10);
    building->show();

    return a.exec();
}
