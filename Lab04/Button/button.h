#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QString text = "Lift Button", QWidget *parent = 0);

    bool isPushed() noexcept;
    void reset() noexcept;

signals:
    void activated();

protected:
    void paintEvent(QPaintEvent *);

private:
    bool isActivated;

private slots:
    void wasClicked() noexcept;
};

#endif // BUTTON_H