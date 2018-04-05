#include <QtWidgets>

#include "lightfinder.h"

LightFinder::LightFinder(int sens, bool SI, double SIT, QObject *parent)
{
    setSensitivity(sens);

    SIT *= 1000;

    if (SI == true) {
        startapIgnore = true;
        ignoreTimer.start(SIT, this);
        qDebug() << "ignore timer start";
    }
}

void LightFinder::getFrame(const cv::Mat &frame)
{
    if (!m_frame.empty()) qDebug() << "Finder dropped frame";
    m_frame = frame;
    if (! m_timer.isActive()) m_timer.start(0, this);
}

void LightFinder::process(cv::Mat frame)
{
    const cv::Mat c_frame = frame.clone();
    std::vector<cv::Vec3f> circles;

    if (startapIgnore == false) {

        frame.convertTo(frame, CV_8UC1, 0.8, 0);
        cv::cvtColor(frame, frame, CV_BGR2HSV);
        cv::inRange(frame, *lColor, *hColor, frame);

        cv::erode(frame, frame, cv::Mat(), cv::Point(-1, -1), 1, 1, 1);   //   |
        cv::dilate(frame, frame, cv::Mat(), cv::Point(-1, -1), 4, 1, 1);  //   |- Cleaning ang blurring
        cv::GaussianBlur(frame, frame, cv::Size(7, 7), 2, 2);             //   |

        cv::HoughCircles(frame, circles, CV_HOUGH_GRADIENT, 1, frame.size().width/8, 100, 20, 25, 500);

        emit matReady(c_frame, circles);

    } else {
        emit matReady(c_frame, circles);
    }


}

void LightFinder::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer.timerId())
    {
        process(m_frame);
        m_frame.release();
        m_timer.stop();
    }
    if (event->timerId() == ignoreTimer.timerId())
    {
        qDebug() << "ignore timer stop";
        ignoreTimer.stop();
        startapIgnore = false;
    }
    return;
}

void LightFinder::setMode(bool mode)
{
    stream = mode;
}

void LightFinder::processFrame(const cv::Mat &frame)
{
    if (stream) process(frame); else getFrame(frame);
}

void LightFinder::setSensitivity(int sens)
{
    sensitivity = sens;
    qDebug() << sensitivity;
}
