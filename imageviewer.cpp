#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void ImageViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_img);
    m_img = {};
}

void ImageViewer::setImage(const QImage &img)
{
    if (!m_img.isNull()) qDebug() << "Viewer dropped frame";
    m_img = img;
    if (m_img.size() != size()) setFixedSize(m_img.size());
    update();
}

