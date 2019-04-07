#include "camerawidget.h"

using namespace cv;
CameraWidget::CameraWidget(QLabel* label, QWidget *parent) : QWidget (parent)
{
    cap.open(0);
    labelCam = label;
    play_ = true;
    detector = FistDetection();
}
void CameraWidget::changePlay(){
    play_=!play_;
}
void CameraWidget::play(){
    while (play_){
        if(!cap.isOpened())  // check if we succeeded
        {
            qDebug("Error openning the default camera");
        }
        while (cv::waitKey(5)<0)
        {
            Mat frame;
            // Get frame
            cap >> frame;
            /*
            if (detector.loadCascade()){
                Movment mvmd = detector.detection(frame);
                emit tryMoveCam(mvmd);
                frame = detector.getDisplayFrame();
            }*/
            img= Mat2QImage(frame,false);
            labelCam->setPixmap(QPixmap::fromImage(img));
            // Resize the label to fit the image
            labelCam->resize(labelCam->pixmap()->size());
        }
    }
    play_=true;
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
