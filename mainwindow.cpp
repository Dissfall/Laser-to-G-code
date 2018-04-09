#include "mainwindow.h"
#include "capture.h"
#include "converter.h"
#include "lightfinder.h"
#include "circlevisualizer.h"
#include "imageviewer.h"
#include "recorder.h"
#include "ui_mainwindow.h"

QSettings *settings = new QSettings("settings.conf", QSettings::NativeFormat);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    if (settings->value("settings/default").toBool() == false) setDefSettings(settings);

    ui->sensitivity->setValue(settings->value("settings/finderSensitivity").toInt());
    ui->finderStartapIgnore->setChecked(settings->value("settings/reduceStartupSens").toBool());
    ui->startapIgnoreTime->setValue(settings->value("settings/startupReduceTime").toDouble());
    ui->laserColor->setCurrentIndex(settings->value("settings/laserColor").toInt());
    ui->recorderShow->setCurrentIndex(settings->value("settings/laserColor").toInt());

    if (ui->finderStartapIgnore->isChecked() == false) ui->startapIgnoreTime->setEnabled(false);

    emit ui->recorder->setTableMode(ui->recorderShow->currentIndex());

    Capture *capture = new Capture();
    LightFinder *finder = new LightFinder(settings->value("settings/finderSensitivity").toInt(),
                                          settings->value("settings/reduceStartupSens").toBool(),
                                          settings->value("settings/startupReduceTime").toDouble());
    CircleVisualizer *visualizer = new CircleVisualizer();
    Converter *converter = new Converter;

    converter->setViewerSize(ui->videoView->size());

    connect(capture, SIGNAL(matReady(cv::Mat)), finder, SLOT(processFrame(cv::Mat)));
    connect(finder, SIGNAL(matReady(cv::Mat, std::vector<cv::Vec3f>)), visualizer, SLOT(processFrame(cv::Mat, std::vector<cv::Vec3f>)));
    connect(finder, SIGNAL(matReady(cv::Mat, std::vector<cv::Vec3f>)), ui->recorder, SLOT(addCircles(cv::Mat, std::vector<cv::Vec3f>)));
    connect(visualizer, SIGNAL(matReady(cv::Mat)), converter, SLOT(processFrame(cv::Mat)));
    connect(converter, SIGNAL(imageReady(QImage)), ui->videoView, SLOT(setImage(QImage)));

    connect(ui->sensitivity, SIGNAL(valueChanged(int)), finder, SLOT(setSensitivity(int)));
    connect(ui->circleSens, SIGNAL(valueChanged(int)), finder, SLOT(setCircleSens(int)));
    connect(ui->finderStartapIgnore, SIGNAL(clicked(bool)), ui->startapIgnoreTime, SLOT(setEnabled(bool)));
    connect(ui->recorderShow, SIGNAL(currentIndexChanged(int)), ui->recorder, SLOT(setTableMode(int)));

    capture->start(1);

}

MainWindow::~MainWindow()
{
    settings->setValue("settings/finderSensitivity", ui->sensitivity->value());
    settings->setValue("settings/laserColor", ui->laserColor->currentIndex());
    settings->setValue("settings/reduceStartupSens", ui->finderStartapIgnore->isChecked());
    settings->setValue("settings/startupReduceTime", ui->startapIgnoreTime->value());
    settings->setValue("settings/recorderShow", ui->recorderShow->currentIndex());
    settings->setValue("settings/unrecordedShow", ui->recorderUnrecordedShow->isChecked());
    settings->sync();

    delete ui;
}

void MainWindow::setDefSettings(QSettings *settings)
{
    settings->setValue("settings/default", true);
    settings->setValue("settings/finderSensitivity", defFinderSensitivity);
    settings->setValue("settings/laserColor", defLaserColor);
    settings->setValue("settings/finderShow", defFinderShow);
    settings->setValue("settings/highlightFounded", defHFP);
    settings->setValue("settings/reduceStartupSens", defReduceStartupSens);
    settings->setValue("settings/startupReduceTime", defStartupReduceTime);
    settings->setValue("settings/recorderShow", defRecorderShow);
    settings->setValue("settings/unrecordedShow", defUnrecordedShow);
    settings->sync();
}

