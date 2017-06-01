#include <QPainter>
#include <QMessageBox>
#include "viewport.h"
#include "wireframeviewer.h"
#include "ui_viewport.h"
#include "rendercalc.h"

void Viewport::drawPoint(QPainter &paint, QPointF point, size_t len)
{
    paint.setPen(QPen(Qt::red, 1, Qt::DashLine));
    paint.drawLine(QPointF(point.x() - len + width()/2, point.y() + height()/2), QPointF(point.x() + len + width()/2, point.y() + height()/2));

    paint.setPen(QPen(Qt::green, 1, Qt::DashLine));
    paint.drawLine(QPointF(point.x() + width()/2 , point.y() - len + height()/2), QPointF(point.x() + width()/2, point.y() + len + height()/2));
}

void Viewport::drawAxes(QPainter &paint)
{
    paint.setPen(QPen(QColor(150, 200, 150)));

    paint.drawLine(QPointF(0, height()/2), QPointF(width(), height()/2));
    paint.drawLine(QPointF(width()/2, 0), QPointF(width()/2, height()));
}

void Viewport::paintEvent(QPaintEvent *)
{

    QPainter paint(this);

    if(par->showAxes())
        drawAxes(paint);

    graph g = constructGraph();
    argument arg = {par->getTransforms(), par->getFileName().toStdString().c_str()};
    command cmd = c_transform;
    if(par->reloadMesh())
    {
        par->setReload(false);
        cmd = c_open;
    }

    int_std flag = getGraph(g, cmd, arg);
    switch(flag)
    {
    case status_ok:
            paint.setPen(QPen(Qt::darkGray, 1, Qt::SolidLine));
            for(size_t i = 0; i < g.edges.size; i++)
            {
                point2d p1 = g.verts.data[g.edges.data[i].starti];
                point2d p2 = g.verts.data[g.edges.data[i].endi];

                paint.drawLine(QPointF(p1.x + width()/2, -p1.y + height()/2), QPointF(p2.x + width()/2, -p2.y + height()/2));
            }
        break;
    case status_invalid_arg_no_file:
        if(cmd == c_open)
        {
            QMessageBox msg;
            msg.setText("Нет входного файла");
            msg.exec();
        }
        break;
    case status_no_mesh:
        break;
    case status_open_file_error:
    {
        QMessageBox msg;
        msg.setText("Некорректный входной файл");
        msg.exec();
    }
        break;
    case status_unknown_command:
    {
        QMessageBox msg;
        msg.setText("Неизвестная команда");
        msg.exec();
    }
        break;

    }

    destroyGraph(g);
    resetButPivot((par->getTransforms()));

    if(par->showPivot())
    {
        drawPoint(paint, QPointF(par->getTransforms().pivotPoint.x, par->getTransforms().pivotPoint.y), par->getPivotShowLen());
    }

    paint.end();
}

Viewport::Viewport(QWidget *parent, WireframeViewer *_par) :
    QWidget(parent), par(_par),
    ui(new Ui::Viewport)
{
    ui->setupUi(this);
}

Viewport::~Viewport()
{
    delete ui;

    argument arg = {par->getTransforms(), nullptr};
    graph g;
    getGraph(g, c_clean, arg);
}
