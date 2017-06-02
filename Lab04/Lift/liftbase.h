#ifndef LIFTBASE_H
#define LIFTBASE_H

#include <QWidget>

class LiftBase : public QWidget
{
    Q_OBJECT
public:
    explicit LiftBase(QColor backColor = Qt::lightGray, QWidget *parent = nullptr);
    ~LiftBase() = default;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor backWallColor;
};

#endif // LIFTBASE_H
