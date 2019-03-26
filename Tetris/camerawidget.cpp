#include "camerawidget.h"

CameraWidget::CameraWidget(QLabel* label, QWidget *parent) : QWidget (parent)
{
    cap.open(0);
    labelCam = label;
    play_ = false;
}
void CameraWidget::changePlay(){
    play_=!play_;
}
void CameraWidget::play(){
    play_ = true;
    while (play_){
        if(!cap.isOpened())  // check if we succeeded
        {
            cerr<<"Error openning the default camera"<<endl;
        }

        CascadeClassifier face_cascade;
        if( !face_cascade.load( "../Tetris/haarcascade_frontalface_alt.xml" ) )
        {
            cerr<<"Error loading haarcascade"<<endl;
        }

        while (waitKey(5)<0)
        {
            Mat frame,frame_gray;
            std::vector<Rect> faces;
            // Get frame
            cap >> frame;
            // Mirror effect
            cv::flip(frame,frame,1);
            // Convert to gray
            cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
            // Equalize graylevels
            //        equalizeHist( frame_gray, frame_gray );
            //-- Detect faces
            face_cascade.detectMultiScale( frame_gray, faces, 1.1, 4, 0|CASCADE_SCALE_IMAGE , Size(60, 60) );
            if (faces.size()>0)
            {
                // Draw green rectangle
                for (int i=0;i<(int)faces.size();i++)
                    rectangle(frame,faces[i],Scalar(0,255,0),2);
            }
            img= Mat2QImage(frame,false);
            labelCam->setPixmap(QPixmap::fromImage(img));
            // Resize the label to fit the image
            labelCam->resize(labelCam->pixmap()->size());
        }
    }
}
QImage CameraWidget::Mat2QImage(cv::Mat const& src,bool flipe)
{
    Mat image = src;
    //cv::resize(image, image, cv::Size(300,300));
    // Flip to get a mirror effect
    if (flipe){
    flip(image,image,1);}
    // Invert Blue and Red color channels
    cvtColor(image,image,COLOR_RGB2BGR);
    // Convert to Qt image
    QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
    return img;
}
