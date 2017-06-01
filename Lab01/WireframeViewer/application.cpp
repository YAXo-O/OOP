#include <QApplication>
#include "application.h"
#include "wireframeviewer.h"

Application::Application(int _argc, char *_argv[]) : argc(_argc), argv(_argv)
{
}

int Application::run()
{
    QApplication a(argc, argv);
    WireframeViewer w;
    w.show();

    return a.exec();
}
