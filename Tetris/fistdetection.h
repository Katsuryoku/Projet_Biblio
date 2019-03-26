#ifndef FISTDETECTION_H
#define FISTDETECTION_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

enum class Movment {kNone, rRight, rLeft, mRight, mLeft};

class FistDetection
{
public:
    FistDetection();
    Movment detection(Mat frame);
};

#endif // FISTDETECTION_H
