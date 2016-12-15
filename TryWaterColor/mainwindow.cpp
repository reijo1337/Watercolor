#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wet_map.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
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

    ui->c_D54A9E->setStyleSheet("background-color: #D54A9E;");
    ui->c_D54A63->setStyleSheet("background-color: #D54A63;");
    ui->c_D5A74A->setStyleSheet("background-color: #D5A74A;");
    ui->c_B6D54A->setStyleSheet("background-color: #B6D54A;");
    ui->c_4AD57A->setStyleSheet("background-color: #4AD57A;");
    ui->c_4AB6D5->setStyleSheet("background-color: #4AB6D5;");
    ui->c_6C4AD5->setStyleSheet("background-color: #6C4AD5;");
    ui->c_954AD5->setStyleSheet("background-color: #954AD5;");
    ui->c_D2CB6B->setStyleSheet("background-color: #D2CB6B;");

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

void MainWindow::on_checkBox_clicked(bool checked)
{
    m_scene->VisualWet(checked);
}

void MainWindow::on_pushButton_4_clicked()
{
    m_scene->ClearAll();
}

void MainWindow::on_c_D54A9E_clicked()
{
    m_scene->setSplatColor(QColor("#D54A9E"));
    ui->colorPicker->setStyleSheet("background-color: #D54A9E;");
}

void MainWindow::on_c_D54A63_clicked()
{
    m_scene->setSplatColor(QColor("#D54A63"));
    ui->colorPicker->setStyleSheet("background-color: #D54A63;");
}

void MainWindow::on_c_D5A74A_clicked()
{
    m_scene->setSplatColor(QColor("#D5A74A"));
    ui->colorPicker->setStyleSheet("background-color: #D5A74A;");
}

void MainWindow::on_c_B6D54A_clicked()
{
    m_scene->setSplatColor(QColor("#B6D54A"));
    ui->colorPicker->setStyleSheet("background-color: #B6D54A;");
}

void MainWindow::on_c_4AD57A_clicked()
{
    m_scene->setSplatColor(QColor("#4AD57A"));
    ui->colorPicker->setStyleSheet("background-color: #4AD57A;");
}

void MainWindow::on_c_4AB6D5_clicked()
{
    m_scene->setSplatColor(QColor("#4AB6D5"));
    ui->colorPicker->setStyleSheet("background-color: #4AB6D5;");
}

void MainWindow::on_c_6C4AD5_clicked()
{
    m_scene->setSplatColor(QColor("#6C4AD5"));
    ui->colorPicker->setStyleSheet("background-color: #6C4AD5;");
}

void MainWindow::on_c_954AD5_clicked()
{
    m_scene->setSplatColor(QColor("#954AD5"));
    ui->colorPicker->setStyleSheet("background-color: #954AD5;");
}

void MainWindow::on_c_D2CB6B_clicked()
{
    m_scene->setSplatColor(QColor("#D2CB6B"));
    ui->colorPicker->setStyleSheet("background-color: #D2CB6B;");
}
