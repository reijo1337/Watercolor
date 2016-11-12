#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    m_scene = new SplatScene();
    m_scene->setSceneRect(0, 0,
                          ui->m_mainView->width() - 2,
                          ui->m_mainView->height() - 2);
    ui->m_mainView->setScene(m_scene);
    ui->m_mainView->setMouseTracking(true);
    connect(m_scene, SIGNAL(mouseMoved(int,int)), this, SLOT(DrawBrushCircle(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{
    m_scene->disableCursor();
}
