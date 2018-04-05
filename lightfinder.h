#ifndef LIGHTFINDER_H
#define LIGHTFINDER_H

#include <QObject>
#include <QBasicTimer>
#include <QDebug>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

class LightFinder : public QObject
{
    Q_OBJECT

    QBasicTimer m_timer, ignoreTimer;
    cv::Mat m_frame;
    bool stream = true;
    int sensitivity = 70;
    const cv::Scalar *lColor = new cv::Scalar(60 - sensitivity, 100, 50);  // lower bound
    const cv::Scalar *hColor = new cv::Scalar(60 + sensitivity, 255, 255); // upper bound
    const double stickSpace = 100;
    double distance;
    cv::Point *point = new cv::Point(-100, -100);
    bool startapIgnore;
    double ignoreTime;

public:
    explicit LightFinder(int sens, bool SI, double SIT, QObject *parent = 0);
    void setMode(bool mode);
    Q_SIGNAL void matReady(const cv::Mat &, const std::vector<cv::Vec3f> &);
    Q_SLOT void processFrame(const cv::Mat & frame);
    Q_SLOT void setSensitivity(int sens);

protected:
    void getFrame(const cv::Mat & frame);
    void process(cv::Mat frame);
    void timerEvent(QTimerEvent *event);
};

#endif // LIGHTFINDER_H
