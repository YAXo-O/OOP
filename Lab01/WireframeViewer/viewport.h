#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>

class WireframeViewer;

namespace Ui {
class Viewport;
}

class Viewport : public QWidget
{
    Q_OBJECT
private:
    WireframeViewer *par;
    Ui::Viewport *ui;

    void drawPoint(QPainter &paint, QPointF point, size_t len);
    void drawAxes(QPainter &paint);

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit Viewport(QWidget *parent = 0, WireframeViewer *_par = 0);
    ~Viewport();
};

#endif // VIEWPORT_H
