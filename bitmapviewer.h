#ifndef BITMAPVIEWER_H
#define BITMAPVIEWER_H

#include <QWidget>

#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

namespace Ui {
class BitmapViewer;
}

class BitmapViewer : public QWidget
{
    Q_OBJECT

public:
    explicit BitmapViewer(QWidget *parent = 0);
    ~BitmapViewer();
    Q_SLOT void setImage(QImage image);

private:
    Ui::BitmapViewer *ui;
};

#endif // BITMAPVIEWER_H
