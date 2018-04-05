#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QThread>
#include <QSettings>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int defFinderSensitivity = 60;
    int defLaserColor = 0;
    int defFinderShow = 1;
    bool defHFP = true;
    bool defReduceStartupSens = true;
    double defStartupReduceTime = 1;
    int defRecorderShow = 0;
    bool defUnrecordedShow = true;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    Q_SLOT void setupTable(int index);

private:
    Ui::MainWindow *ui;
    void setDefSettings(QSettings *settings);
};

#endif // MAINWINDOW_H
