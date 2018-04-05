#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QtWidgets>
#include <QTimer>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

class Converter : public QObject
{
    Q_OBJECT

    QBasicTimer m_timer;
    cv::Mat m_frame;
    bool stream = true;

public:
    explicit Converter(QObject * = 0);
    void setMode(bool mode);
    Q_SIGNAL void imageReady(const QImage &);
    Q_SLOT void processFrame(const cv::Mat & frame);

protected:
    static void matDeleter(void *mat);
    void getFrame(const cv::Mat & frame);
    void process(cv::Mat frame);
    void timerEvent(QTimerEvent *event);
};

#endif // CONVERTER_H
