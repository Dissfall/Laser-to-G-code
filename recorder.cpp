#include <QHeaderView>

#include "recorder.h"

Recorder::Recorder(QWidget *parent) : QTableWidget(parent)
{
    this->setAutoScroll(true);
}

void Recorder::enableRecord()
{
    recordEnabled = true;
}

void Recorder::disableRecord()
{
    recordEnabled = false;
}

void Recorder::addCircles(cv::Mat, std::vector<cv::Vec3f> circles)
{
    if (recordEnabled == true)
    {
        if (circles.size() > 0)
        {
            circleStorage.insert(circleStorage.end(), circles.begin(), circles.end());
            currentCircle += circles.size();

            if (currentMode == 1)
            {

            } else
            {
                for (int i = 0; i <= circles.size(); i++)
                {
                    if (QString::compare(QString::number(circles[i][0]), "0", Qt::CaseInsensitive) && !QString::number(circles[i][1]).contains("-"))
                    {
                        this->insertRow(this->rowCount());
                        this->setItem(this->rowCount() - 1, 0, new QTableWidgetItem(QString::number(circles[i][0])));
                        this->setItem(this->rowCount() - 1, 1, new QTableWidgetItem(QString::number(circles[i][1])));
                        coors << QString::number(circles[i][0]) << QString::number(circles[i][1]);
                    }
                }
            }
        }
    }
}

void Recorder::clearRecord()
{
    circleStorage.clear();

    for (int i = 0; i <= this->rowCount(); i++)
    {
        this->removeRow(i);
    }
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

    if (mode == 1)
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

void Recorder::saveFile()
{
    qDebug() << "save";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save coordinates to file"), "~/untitled", tr("Text files (*.txt);; G-code files (*.gcode)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QTextStream out(&file);
//        out.setVersion(QDataStream::Qt_4_5);
        qDebug() << coors;
        for (int i = 0; i < coors.length(); i += 2)
        {
            out << coors.at(i).toUtf8() << " " << coors.at(i + 1).toUtf8() << "\r\n";
        }
        file.close();
    } else {
        return;
    }
}
