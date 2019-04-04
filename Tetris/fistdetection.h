#ifndef FISTDETECTION_H
#define FISTDETECTION_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

typedef enum class Movment {kNone, rRight, rLeft, mRight, mLeft};

class FistDetection
{
private:
    Mat displayFrame;
    vector<Point> currentFistCenters;
    CascadeClassifier face_cascade;
    int divisionDetect = 4;
    int heigthDetect = 15;
public:
    FistDetection();
    bool loadCascade();
    bool loadCascade(String path);
    Movment detection(Mat frame);
    void setDivisionDetect(int value){divisionDetect=value;}
    Mat getDisplayFrame(){return displayFrame;}
};

#endif // FISTDETECTION_H
