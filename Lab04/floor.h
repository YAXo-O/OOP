#ifndef FLOOR_H
#define FLOOR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Floor : public QWidget
{
    Q_OBJECT
public:
    explicit Floor(int floorNum, QColor wallColor = Qt::cyan, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int floorNum;
    QPushButton *callPB;
    QColor wallColor;
    QLabel *floorLab;
};

#endif // FLOOR_H
