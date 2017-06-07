#ifndef LIFTPANEL_H
#define LIFTPANEL_H

#include <QWidget>
#include <QLCDNumber>

class LiftPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LiftPanel(int floors, QWidget *parent = nullptr);

public slots:
    void updateFloor(int floor) noexcept;

signals:
    void callFloor(int, int);

private slots:
    void buttonPressed();

private:
    QLCDNumber *lcdNum;

};

#endif // LIFTPANEL_H
