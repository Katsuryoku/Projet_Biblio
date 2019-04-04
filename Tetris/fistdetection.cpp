#include "fistdetection.h"

FistDetection::FistDetection()
{
}
bool FistDetection::loadCascade()
{
    if( !face_cascade.load( "../Tetris/closed_palm.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
        return false;
    }else {
        return true;
    }
}
bool FistDetection::loadCascade(String path)
{
    if( !face_cascade.load(path) )
    {
        cerr<<"Error loading haarcascade"<<endl;
        return false;
    }else {
        return true;
    }
}
Movment FistDetection::detection(Mat frame)
{
    Mat frame_gray;
    std::vector<Rect> fits;
    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    // Equalize graylevels
    //        equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, fits, 1.1, 4, 0|CASCADE_SCALE_IMAGE , Size(60, 60) );
    if (fits.size()==2)
    {
        currentFistCenters.clear();
        // Draw green rectangle
        for (int i=0;i<(int)fits.size();i++)
        {
            rectangle(frame,fits[i],Scalar(0,255,0),2);
            Point center_of_rect = (fits[i].br() + fits[i].tl())*0.5;
            currentFistCenters.push_back(center_of_rect);
            circle(frame,center_of_rect,3,Scalar(0,0,255));
        }
        // x/width horizontal axis for point
        // y/heigth vertical axis for point
        /*
        0/0---X--->
         |
         |
         Y
         |
         |
         v
         */

        // We want to know if it's fist[0] was the right or left fist
        if (currentFistCenters[0].x<currentFistCenters[1].x) // left
        {
            /** Rotation **/
            // if fist together :
            if (currentFistCenters[1].inside(Rect(currentFistCenters[0].x,currentFistCenters[0].y-heigthDetect,frame.cols/4,20)))
            {
                rectangle(frame,Rect(currentFistCenters[0].x,currentFistCenters[0].y-heigthDetect,frame.cols/4,20),Scalar(255,0,0),2);
                displayFrame = frame;
                return Movment::rRight;
            }
            else{
                displayFrame = frame;
                /** Movment **/
                if (currentFistCenters[0].y+heigthDetect<currentFistCenters[1].y)
                {
                    return Movment::mRight;
                }else{
                    if (currentFistCenters[0].y>currentFistCenters[1].y+heigthDetect){
                        return Movment::mLeft;
                    }
                }
            }
        }else{
            /** Rotation **/
            // if fist together :
            if (currentFistCenters[0].inside(Rect(currentFistCenters[1].x,currentFistCenters[1].y-heigthDetect,frame.cols/4,20)))
            {

                rectangle(frame,Rect(currentFistCenters[1].x,currentFistCenters[1].y-heigthDetect,frame.cols/4,20),Scalar(255,0,0),2);
                displayFrame = frame;
                return Movment::rRight;
            }
            else{
                displayFrame = frame;
                /** Movment **/
                if (currentFistCenters[0].y+heigthDetect<currentFistCenters[1].y)
                {
                    return Movment::mLeft;
                }else{
                    if (currentFistCenters[0].y>currentFistCenters[1].y+heigthDetect){
                        return Movment::mRight;
                    }
                }
            }
        }

    }
    displayFrame = frame;
    return Movment::kNone;
}
