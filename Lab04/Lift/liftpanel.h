#ifndef LIFTPANEL_H
#define LIFTPANEL_H

#include <QWidget>
#include <QLCDNumber>
#include "../Button/button.h"

class LiftPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LiftPanel(int floors, QWidget *parent = nullptr);

public slots:
    void updateFloor(int floor) noexcept;
    void reachedFloor(int floor) throw(std::out_of_range);

signals:
    void callFloor(int, int);

private slots:
    void buttonPressed();

private:
    QLCDNumber *lcdNum;
    Button *buttons;
    int count;

};

#endif // LIFTPANEL_H
