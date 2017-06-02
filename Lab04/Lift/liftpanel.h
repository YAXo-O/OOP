#ifndef LIFTPANEL_H
#define LIFTPANEL_H

#include <QWidget>

class LiftPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LiftPanel(int floors, QWidget *parent = nullptr);

};

#endif // LIFTPANEL_H
