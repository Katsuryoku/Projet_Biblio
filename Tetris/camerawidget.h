#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <QWidget>
#include <cstdio>
#include <iostream>
#include <QLabel>
#include "fistdetection.h"

using namespace std;
class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(QLabel* label, QWidget *parent = nullptr);
private:
    cv::VideoCapture cap;
    QImage Mat2QImage(cv::Mat const& src,bool flipe =true);
    cv::Mat frame;
    QImage img;
    QLabel* labelCam;
    FistDetection detector;
    bool play_ = false;
signals:
    void tryMoveCam(Movment mvm);
public slots:
    void changePlay();
    void play();
};

#endif // CAMERAWIDGET_H
