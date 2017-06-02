#ifndef TUNNEL_H
#define TUNNEL_H

#include <QWidget>
#include "lift/liftbase.h"

class Tunnel : public QWidget
{
    Q_OBJECT
public:
    explicit Tunnel(LiftBase *lift, QColor bgColor = Qt::black, QWidget *parent = nullptr);

    void fromFloorHeight(int height) noexcept;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor bgColor;
    LiftBase *lift;
};

#endif // TUNNEL_H
