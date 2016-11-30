#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <splat_scene.h>
#include <QGraphicsEllipseItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void mouseMoveEvent(QMouseEvent *);

private slots:
    void on_colorPicker_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_simpleChoice_clicked();

    void on_wetOnDryCoice_clicked();

    void on_cruncyChoice_clicked();

    void on_wetOnWetChoice_clicked();

    void on_blobbChoice_clicked();

private:
    SplatScene *m_scene;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
