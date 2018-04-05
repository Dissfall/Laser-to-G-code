#ifndef CIRCLEVISUALIZER_H
#define CIRCLEVISUALIZER_H

#include <QObject>
#include <QDebug>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

class CircleVisualizer : public QObject
{
    Q_OBJECT


public:
    CircleVisualizer(QWidget *parent = 0);
    Q_SIGNAL void matReady(const cv::Mat &);
    Q_SLOT void processFrame(const cv::Mat &, const std::vector<cv::Vec3f> &);

protected:
    void process(cv::Mat, std::vector<cv::Vec3f>);
};

#endif // CIRCLEVISUALIZER_H
