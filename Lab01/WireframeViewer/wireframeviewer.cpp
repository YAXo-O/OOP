#include <QFileDialog>
#include <QValidator>
#include "meshreader.h"
#include "wireframeviewer.h"
#include "ui_wireframeviewer.h"
#include "viewport.h"

QString WireframeViewer::getFileName() const
{
    return fileName;
}

float WireframeViewer::getPivotShowLen() const
{
    return pivotShowLen;
}

bool WireframeViewer::reloadMesh() const
{
    return bRemakeMesh;
}

void WireframeViewer::setReload(bool bSet)
{
    bRemakeMesh = bSet;
}

void WireframeViewer::connectInput()
{
    connect(ui->x_move_line, SIGNAL(returnPressed()), this, SLOT(setDx()));
    connect(ui->y_move_line, SIGNAL(returnPressed()), this, SLOT(setDy()));
    connect(ui->z_move_line, SIGNAL(returnPressed()), this, SLOT(setDz()));
    connect(ui->x_factor_rot_line, SIGNAL(returnPressed()), this, SLOT(setDtx()));
    connect(ui->y_factor_rot_line, SIGNAL(returnPressed()), this, SLOT(setDty()));
    connect(ui->z_factor_rot_line, SIGNAL(returnPressed()), this, SLOT(setDtz()));
    connect(ui->x_factor_scale_line, SIGNAL(returnPressed()), this, SLOT(setSx()));
    connect(ui->y_factor_scale_line, SIGNAL(returnPressed()), this, SLOT(setSy()));
    connect(ui->z_factor_scale_line, SIGNAL(returnPressed()), this, SLOT(setSz()));
    connect(ui->x_pivot_line, SIGNAL(returnPressed()), this, SLOT(setPivotPointX()));
    connect(ui->y_pivot_line, SIGNAL(returnPressed()), this, SLOT(setPivotPointY()));
    connect(ui->z_pivot_line, SIGNAL(returnPressed()), this, SLOT(setPivotPointZ()));
    connect(ui->axes_check, SIGNAL(clicked(bool)), this, SLOT(setShowAxes(bool)));
    connect(ui->pivot_check, SIGNAL(clicked(bool)), this, SLOT(setShowPivot(bool)));
    connect(ui->load_file_pb, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->pivot_len_line, SIGNAL(returnPressed()), this, SLOT(setPivotShowLen()));
    connect(ui->reset_transform_pb, SIGNAL(clicked()), this, SLOT(resetTransMatrix()));
    connect(ui->turn_table_pb, SIGNAL(clicked()), this, SLOT(doTurnTable()));
    connect(turnTableTimer, SIGNAL(timeout()), this, SLOT(turnTableActon()));
}

void WireframeViewer::validateInput()
{
    // Зададим ограничение ввода!
    QDoubleValidator *valid = new QDoubleValidator();
    valid->setLocale(QLocale("USA"));

    ui->x_move_line->setValidator(valid);
    ui->y_move_line->setValidator(valid);
    ui->z_move_line->setValidator(valid);

    ui->x_factor_rot_line->setValidator(valid);
    ui->y_factor_rot_line->setValidator(valid);
    ui->z_factor_rot_line->setValidator(valid);

    ui->x_factor_scale_line->setValidator(valid);
    ui->y_factor_scale_line->setValidator(valid);
    ui->z_factor_scale_line->setValidator(valid);

    ui->x_pivot_line->setValidator(valid);
    ui->y_pivot_line->setValidator(valid);
    ui->z_pivot_line->setValidator(valid);

    ui->pivot_len_line->setValidator(valid);

    ui->x_rot_rate_line->setValidator(valid);
    ui->y_rot_rate_line->setValidator(valid);
    ui->z_rot_rate_line->setValidator(valid);

}

WireframeViewer::WireframeViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WireframeViewer),
    bRemakeMesh(false),
    bShowAxes(false), bShowPivot(false),
    pivotShowLen(40), bTurnTable(false),
    turnTableTimer(new QTimer)
{
    ui->setupUi(this);
    v = new Viewport(ui->viewport_placeholder, this);
    ui->viewport_layout->addWidget(v);

    meshTransforms = new transformations;
    resetTransforms(*meshTransforms);

    connectInput();

    validateInput();
}

WireframeViewer::~WireframeViewer()
{
    delete ui;
    delete meshTransforms;
    if(turnTableTimer != nullptr)
        delete turnTableTimer;
}

transformations &WireframeViewer::getTransforms()
{
    return *meshTransforms;
}

bool WireframeViewer::showAxes()
{
    return bShowAxes;
}

bool WireframeViewer::showPivot()
{
    return bShowPivot;
}

// Слоты - обработка ввода
// Накинуть валидатор на поля ввода
void WireframeViewer::setDx()
{
    meshTransforms->dx = ui->x_move_line->text().toFloat();
    meshTransforms->bMove = true;
    v->repaint();
}

void WireframeViewer::setDy()
{
    meshTransforms->dy = ui->y_move_line->text().toFloat();
    meshTransforms->bMove = true;
    v->repaint();
}

void WireframeViewer::setDz()
{
    meshTransforms->dz = ui->z_move_line->text().toFloat();
    meshTransforms->bMove = true;
    v->repaint();
}

void WireframeViewer::setDtx()
{
    meshTransforms->dtx = ui->x_factor_rot_line->text().toFloat()*degToRad;
    meshTransforms->bRotate = true;

    v->repaint();
}

void WireframeViewer::setDty()
{
    meshTransforms->dty = ui->y_factor_rot_line->text().toFloat()*degToRad;
    meshTransforms->bRotate = true;

    v->repaint();
}

void WireframeViewer::setDtz()
{
    meshTransforms->dtz = ui->z_factor_rot_line->text().toFloat()*degToRad;
    meshTransforms->bRotate = true;

    v->repaint();
}

void WireframeViewer::setSx()
{
    meshTransforms->sx = ui->x_factor_scale_line->text().toFloat();
    meshTransforms->bScale = true;

    v->repaint();
}

void WireframeViewer::setSy()
{
    meshTransforms->sy = ui->y_factor_scale_line->text().toFloat();
    meshTransforms->bScale = true;

    v->repaint();
}

void WireframeViewer::setSz()
{
    meshTransforms->sz = ui->z_factor_scale_line->text().toFloat();
    meshTransforms->bScale = true;

    v->repaint();
}

void WireframeViewer::setPivotPointX()
{
    meshTransforms->pivotPoint.x = ui->x_pivot_line->text().toFloat();

    v->repaint();
}

void WireframeViewer::setPivotPointY()
{
    meshTransforms->pivotPoint.y = -ui->y_pivot_line->text().toFloat();

    v->repaint();
}

void WireframeViewer::setPivotPointZ()
{
    meshTransforms->pivotPoint.z = ui->z_pivot_line->text().toFloat();

    v->repaint();
}

void WireframeViewer::setShowAxes(bool bShow)
{
    bShowAxes = bShow;
    v->repaint();
}

void WireframeViewer::setShowPivot(bool bShow)
{
    bShowPivot = bShow;
    v->repaint();
}

void WireframeViewer::loadFile()
{
    fileName = QFileDialog::getOpenFileName(nullptr, "Выберите файл модели", QString(), "*.obj");
    bRemakeMesh = true;
    v->repaint();
}

void WireframeViewer::setPivotShowLen()
{
    pivotShowLen = ui->pivot_len_line->text().toFloat();
    if(bShowPivot)
        v->repaint();
}

void WireframeViewer::resetTransMatrix()
{
    meshTransforms->bReset = true;
    v->repaint();
}

void WireframeViewer::doTurnTable()
{
    if(!bTurnTable)
    {
        ui->turn_table_pb->setText("Остановить!");

        bTurnTable = true;

        turnTableTimer->start(33);
    }
    else
    {
        ui->turn_table_pb->setText("Turn Table");

        bTurnTable = false;

        turnTableTimer->stop();
    }

}

void WireframeViewer::turnTableActon()
{
    meshTransforms->bRotate = true;
    meshTransforms->dtx = ui->x_rot_rate_line->text().toFloat();
    meshTransforms->dty = ui->y_rot_rate_line->text().toFloat();
    meshTransforms->dtz = ui->z_rot_rate_line->text().toFloat();

    v->repaint();

    turnTableTimer->start(33);
}
