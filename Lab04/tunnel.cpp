#include <QPainter>
#include "tunnel.h"

Tunnel::Tunnel(LiftBase *_lift, QColor _bgColor, QWidget *parent) : QWidget(parent), bgColor(_bgColor), lift(_lift)
{
    if(lift)
        lift->setParent(this);
}

void Tunnel::fromFloorHeight(int height) noexcept
{
    setFixedWidth(height);
    if(lift)
    {
        lift->setFixedSize(height, height);
        lift->move(0, this->height() - height);
    }
}

void Tunnel::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(rect(), bgColor);

    p.end();
}
