#ifndef LIFTDOORS_H
#define LIFTDOORS_H

#include <QWidget>

class LiftDoors : public QWidget
{
    Q_OBJECT
public:
    explicit LiftDoors(QColor col = Qt::darkGray, QWidget *parent = 0);
    ~LiftDoors() = default;

    void setDoor(float doorOpen, float preDoorOpen);

protected:
    void paintEvent(QPaintEvent *pe) override;

private:
    QColor doorCol;
    float doorFill;
    float preDoorFill;

};

#endif // LIFTDOORS_H
