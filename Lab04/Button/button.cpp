#include <QPainter>
#include "button.h"

Button::Button(QString text, QWidget *parent) : QPushButton(text, parent), isActivated(false)
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
