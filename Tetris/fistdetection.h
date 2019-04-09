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
/* Autor : Thomas Mion */
using namespace std;
// Enum type that stock all movment that can be detected
enum Movment {kNone, rRight, rLeft, mRight, mLeft};
// Class that permit to detect fist
class FistDetection
{
private:
    // Frame to display
    cv::Mat displayFrame;
    // Fist centers detected
    vector<cv::Point> currentFistCenters;
    // Cascade used
    cv::CascadeClassifier face_cascade;
    // number of time that width frame it divide for create the width of the rectangle for double fists
    int divisionDetect = 4;
    // number of pixel of heigth of the rectangle for double fists
    int heigthDetect = 15;
public:
    // Constructor
    FistDetection();
    // Load default cascade
    bool loadCascade();
    // Load personal cascade
    bool loadCascade(cv::String path);
    // detect movment from a frame
    Movment detection(cv::Mat frame);
    void setDivisionDetect(int value){divisionDetect=value;}
    cv::Mat getDisplayFrame(){return displayFrame;}
};

#endif // FISTDETECTION_H
