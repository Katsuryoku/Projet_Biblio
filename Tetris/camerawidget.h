#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
#include "opencv2/opencv.hpp"
#elif CV_MAJOR_VERSION == 4
#include <opencv2/videoio.hpp>
#endif
#include <QWidget>
#include <cstdio>
#include <iostream>
#include <QLabel>
#include "fistdetection.h"

/* Autor : Thomas Mion */
using namespace std;
class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    // Constructor
    explicit CameraWidget(QLabel* label, QWidget *parent = nullptr);
private:
    // cam object
    cv::VideoCapture cap;
    // frame captured by cap
    cv::Mat frame_;
    // image transformed
    QImage img_;
    // label where display img
    QLabel* labelCam;
    // fist detector
    FistDetection detector;
    // boolean to know if we play or not
    bool play_ = false;
    // Transform Mat to QImage to display it
    QImage Mat2QImage(cv::Mat const& src,bool flipe =true);
signals:
    void tryMoveCam(Movment mvm);
public slots:
    // 2 methods to display or not the camera.
    void changePlay();
    void play();
};

#endif // CAMERAWIDGET_H
