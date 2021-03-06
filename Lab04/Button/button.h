#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(int floor = 0, QString text = "Lift Button", QWidget *parent = 0);

    bool isPushed() noexcept;
    void reset() noexcept;

    void setFloor(int floor) noexcept;
    int getFloor() noexcept;

signals:
    void activated();

protected:
    void paintEvent(QPaintEvent *);

private:
    bool isActivated;
    int floor;

private slots:
    void wasClicked() noexcept;
};

#endif // BUTTON_H
