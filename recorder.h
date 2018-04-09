#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QDebug>
#include <QTableWidget>
#include <QtWidgets>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

class Recorder : public QTableWidget
{
    Q_OBJECT

    std::vector<cv::Vec3f> circleStorage;
    int currentCircle = 0;
    int currentMode;

public:
    Recorder(QWidget *parent = 0);
    Q_SLOT void setTableMode(int);
    Q_SLOT void addCircles(cv::Mat, std::vector<cv::Vec3f>);

private:
    void updateTable();
};

#endif // RECORDER_H
