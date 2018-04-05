#include <QHeaderView>

#include "recorder.h"

Recorder::Recorder(QWidget *parent) : QTableWidget(parent)
{

}

void Recorder::addCircles(cv::Mat, std::vector<cv::Vec3f> circles)
{
    for (int i = 0; i <= circles.size(); i++)
    {
        circleStorage[currentCircle] = circles[i];
        currentCircle++;
        qDebug() << "new";
    }
    updateTable();

}

void Recorder::updateTable()
{
    if (currentMode == 0)
    {

    } else
    {
        for (int i = 0; i <= circleStorage.size(); i++)
        {
            this->insertRow(this->rowCount());
            this->setItem(this->rowCount() - 1, 0, new QTableWidgetItem(circleStorage[i][0]));
            this->setItem(this->rowCount() - 1, 1, new QTableWidgetItem(circleStorage[i][1]));
        }
    }
}

void Recorder::setTableMode(int mode)
{
    currentMode = mode;

    if (mode == 0)
    {
        this->setColumnCount(1);
        this->setHorizontalHeaderLabels(QStringList() << tr("code"));
        for (int c = 0; c < this->horizontalHeader()->count(); ++c)
        {
            this->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
        }
    } else
    {
        this->setColumnCount(2);
        this->setHorizontalHeaderLabels(QStringList() << tr("X") << tr("Y"));
        for (int c = 0; c < this->horizontalHeader()->count(); ++c)
        {
            this->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
        }
    }
}
