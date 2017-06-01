#include <QApplication>
#include "floor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;

    Floor test(0);
    test.show();

    return a.exec();
}
