#include "bitmapviewer.h"
#include "ui_bitmapviewer.h"

BitmapViewer::BitmapViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitmapViewer)
{
    ui->setupUi(this);
}

BitmapViewer::~BitmapViewer()
{
    delete ui;
}

void BitmapViewer::setImage(QImage image)
{
    ui->bitmapViewer->setImage(image);
}
