#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtWidgets>

class ImageViewer : public QWidget
{
    Q_OBJECT
    QImage m_img;

protected:
    void paintEvent(QPaintEvent *);

public:
    explicit ImageViewer(QWidget *parent = 0);
    Q_SLOT void setImage(const QImage &img);
};


#endif // IMAGEVIEWER_H
