#include <QPainter>
#include <QHBoxLayout>
#include "liftbase.h"

LiftBase::LiftBase(QColor backColor, QWidget *parent) : QWidget(parent), backWallColor(backColor)
{
}

void LiftBase::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(), backWallColor);
    p.setPen(QPen(Qt::darkGray, 8));
    p.drawLine(0, 4, width(), 4);
    p.drawLine(0, height()-4, width(), height()-4);

    p.end();
}
