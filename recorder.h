#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QDebug>
#include <QTableWidget>
#include <QtWidgets>
#include <QFileDialog>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

class Recorder : public QTableWidget
{
    Q_OBJECT

    std::vector<cv::Vec3f> circleStorage;
    int currentCircle = 0;
    int currentMode;
    QStringList coors;
    bool recordEnabled = false;

public:
    Recorder(QWidget *parent = 0);
    Q_SLOT void setTableMode(int);
    Q_SLOT void addCircles(cv::Mat, std::vector<cv::Vec3f>);
    Q_SLOT void enableRecord();
    Q_SLOT void disableRecord();
    Q_SLOT void clearRecord();
    Q_SLOT void saveFile();

private:
    void updateTable();
};

#endif // RECORDER_H
