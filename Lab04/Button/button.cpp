#include <QPainter>
#include "button.h"

Button::Button(int _floor, QString text, QWidget *parent) : QPushButton(text, parent), isActivated(false), floor(_floor)
{
    connect(this, SIGNAL(clicked()), this, SLOT(wasClicked()));
}

bool Button::isPushed() noexcept
{
    return isActivated;
}

void Button::reset() noexcept
{
    isActivated = false;
    repaint();
}

void Button::setFloor(int _floor) noexcept
{
    floor = _floor;
}

int Button::getFloor() noexcept
{
    return floor;
}

void Button::paintEvent(QPaintEvent *event)
{
    if(isActivated)
    {
        QPainter p(this);

        p.fillRect(rect(), Qt::red);

        p.end();
    }

    QPushButton::paintEvent(event);
}

void Button::wasClicked() noexcept
{
    if(!isActivated)
    {
        isActivated = true;
        update();
        emit activated();
    }
}
