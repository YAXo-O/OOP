#include <QApplication>
#include "buildingdesigner.h"
#include "Lift/liftbase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;

    BuildingDesigner designer;
    Building *building = designer.constructBuilding(12);
    building->show();

    return a.exec();
}
