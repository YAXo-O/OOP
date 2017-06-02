#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QLabel>
#include "Button/button.h"

class Floor : public QWidget
{
    Q_OBJECT
public:
    explicit Floor(int floorNum = 0, QColor wallColor = Qt::cyan, QWidget *parent = nullptr);
    ~Floor() = default;

    void changeFloor(int newNum) noexcept;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    static const QString floorSignPrefix;

    int floorNum;
    Button *callPB;
    QColor wallColor;
    QLabel *floorLab;
};

#endif // FLOOR_H
