#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QDebug>
#include <QBasicTimer>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

class Capture : public QObject
{
    Q_OBJECT
    cv::VideoCapture m_videoCapture;

public:
    explicit Capture(QObject *parent = 0) ;
    Q_SIGNAL void started();
    Q_SLOT void start(int cam = 0);
    Q_SLOT void stop();
    Q_SIGNAL void matReady(const cv::Mat &);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QBasicTimer m_timer;
};

#endif // CAPTURE_H
