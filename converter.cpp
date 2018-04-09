#include "converter.h"

Converter::Converter(QObject *)
{

}

void Converter::matDeleter(void *mat)
{
    delete static_cast<cv::Mat*>(mat);
}

void Converter::getFrame(const cv::Mat &frame)
{
    if (!m_frame.empty()) qDebug() << "Converter dropped frame";
    m_frame = frame;
    if (! m_timer.isActive()) m_timer.start(0, this);
}

void Converter::process(cv::Mat frame)
{
    if ((viewerSize.width() / static_cast<float>(frame.cols)) < viewerSize.height() / static_cast<float>(frame.rows))
    {
        cv::resize(frame, frame, cv::Size(), viewerSize.width() / static_cast<float>(frame.cols), viewerSize.width() / static_cast<float>(frame.cols), cv::INTER_AREA);
    } else {
        cv::resize(frame, frame, cv::Size(), viewerSize.height() / static_cast<float>(frame.rows), viewerSize.height() / static_cast<float>(frame.rows), cv::INTER_AREA);
    }
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    const QImage image(frame.data, frame.cols, frame.rows, frame.step,
                       QImage::Format_RGB888, &matDeleter, new cv::Mat(frame));
    Q_ASSERT(image.constBits() == frame.data);
    emit imageReady(image);
}

void Converter::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != m_timer.timerId()) return;
    process(m_frame);
    m_frame.release();
}

void Converter::setMode(bool mode)
{
    stream = mode;
}

void Converter::processFrame(const cv::Mat &frame)
{
    if (stream) process(frame); else getFrame(frame);
    m_timer.stop();
}

void Converter::setViewerSize(QSize size)
{
    viewerSize = size;
}
