#ifndef FISTDETECTION_H
#define FISTDETECTION_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
#include "opencv2/opencv.hpp"
#elif CV_MAJOR_VERSION == 4
#include <opencv2/videoio.hpp>
#endif
#include <cstdio>
#include <iostream>

using namespace std;

typedef enum class Movment {kNone, rRight, rLeft, mRight, mLeft};

class FistDetection
{
private:
    cv::Mat displayFrame;
    vector<cv::Point> currentFistCenters;
    cv::CascadeClassifier face_cascade;
    int divisionDetect = 4;
    int heigthDetect = 15;
public:
    FistDetection();
    bool loadCascade();
    bool loadCascade(cv::String path);
    Movment detection(cv::Mat frame);
    void setDivisionDetect(int value){divisionDetect=value;}
    cv::Mat getDisplayFrame(){return displayFrame;}
};

#endif // FISTDETECTION_H
