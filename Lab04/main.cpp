#include <QApplication>
#include "buildingdesigner.h"
#include "Lift/liftbase.h"
#include "Lift/liftpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;

    BuildingDesigner designer;
    Building *building = designer.constructBuilding(11);
    building->show();

    LiftPanel panel(11);
    panel.show();

    return a.exec();
}
