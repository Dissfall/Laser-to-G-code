#include <QtWidgets>

#include "capture.h"

Capture::Capture(QObject *)
{

}

void Capture::start(int cam)
{
    if (!m_videoCapture.isOpened())
    {
        qDebug() << "Opening stream...";
        m_videoCapture.open(cam);
        m_timer.start(0, this);
        emit started();
    }
}

void Capture::stop()
{
    m_timer.stop();
    return;
}

void Capture::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != m_timer.timerId()) return;
    cv::Mat frame;
    if (!m_videoCapture.read(frame))
    {
        m_timer.stop();
        return;
    }
    emit matReady(frame);
}
