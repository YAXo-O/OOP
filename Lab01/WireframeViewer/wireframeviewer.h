#ifndef WIREFRAMEVIEWER_H
#define WIREFRAMEVIEWER_H

#include <QMainWindow>
#include <QTimer>
#include "viewport.h"
#include "transformations.h"
#include "wireframe.h"

namespace Ui {
class WireframeViewer;
}

class WireframeViewer : public QMainWindow
{
    Q_OBJECT

private:
    Ui::WireframeViewer *ui;
    Viewport *v;
    transformations *meshTransforms;
    QString fileName;
    bool bRemakeMesh; // Загрузить в память новую модель?

    bool bShowAxes;
    bool bShowPivot;

    float pivotShowLen;
    bool bTurnTable;
    QTimer *turnTableTimer;

    void connectInput();
    void validateInput();

public:
    explicit WireframeViewer(QWidget *parent = 0);
    ~WireframeViewer();

    transformations &getTransforms();

    bool showAxes();
    bool showPivot();

    QString getFileName() const;
    float getPivotShowLen() const;
    bool reloadMesh() const;
    void setReload(bool bSet);

private slots:
    void setDx();
    void setDy();
    void setDz();
    void setDtx();
    void setDty();
    void setDtz();
    void setSx();
    void setSy();
    void setSz();
    void setPivotPointX();
    void setPivotPointY();
    void setPivotPointZ();
    void setShowAxes(bool);
    void setShowPivot(bool);
    void loadFile();
    void setPivotShowLen();
    void resetTransMatrix();
    void doTurnTable(); // По нажатию кнопки
    void turnTableActon(); // Таймер нового кадра анимации

};

#endif // WIREFRAMEVIEWER_H
