#include <QApplication>
#include "buildingdesigner.h"
#include "Lift/liftbase.h"
#include "Lift/liftpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;

    BuildingDesigner designer;
    Building *building = designer.constructBuilding(12);
    building->show();

    int res = a.exec();
    delete building;

    return res;
}
