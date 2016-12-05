#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wet_map.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //srand(time(0));
    ui->setupUi(this);
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    m_scene = new SplatScene();
    m_scene->setSceneRect(0, 0,
                          ui->m_mainView->width() - 2,
                          ui->m_mainView->height() - 2);
    WetMap wetMap(ui->m_mainView->width() - 2,
                  ui->m_mainView->height() - 2);
    m_scene->setWetMap(wetMap);
    ui->m_mainView->setScene(m_scene);
    ui->m_mainView->setMouseTracking(true);

    QPalette myPalette = ui->colorPicker->palette();
    myPalette.setColor( ui->colorPicker->backgroundRole(), QColor(255,0,0) );
    ui->colorPicker->setStyleSheet("background-color: " + QColor(Qt::red).name() + ";");

    connect(ui->brushSize, SIGNAL(valueChanged(int)), m_scene, SLOT(updateBrushWidth(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{
    m_scene->disableCursor();
    QPalette myPalette = ui->colorPicker->palette();
    myPalette.setColor( ui->colorPicker->backgroundRole(), QColor(255,0,0) );
    ui->colorPicker->setPalette( myPalette );
}

void MainWindow::on_colorPicker_clicked()
{
    QColor getColor;

    getColor = QColorDialog::getColor(Qt::white, this);

    ui->colorPicker->setStyleSheet("background-color: " + getColor.name() + ";");
    m_scene->setSplatColor(getColor);
}

void MainWindow::on_pushButton_clicked()
{
    m_scene->setSplatColor(QColor(Qt::red));
}

void MainWindow::on_pushButton_2_clicked()
{
    m_scene->setSplatColor(QColor(Qt::blue));
}

void MainWindow::on_pushButton_3_clicked()
{
    m_scene->setSplatColor(QColor(Qt::green));
}

void MainWindow::on_simpleChoice_clicked()
{
    m_scene->setGenerateStrategy(SplatScene::Simple);
}

void MainWindow::on_wetOnDryCoice_clicked()
{
    m_scene->setGenerateStrategy(SplatScene::WetOnDry);
}

void MainWindow::on_cruncyChoice_clicked()
{
    m_scene->setGenerateStrategy(SplatScene::Cruncy);
}

void MainWindow::on_wetOnWetChoice_clicked()
{
    m_scene->setGenerateStrategy(SplatScene::WetOnWet);
}

void MainWindow::on_blobbChoice_clicked()
{
    m_scene->setGenerateStrategy(SplatScene::Blobby);
}
