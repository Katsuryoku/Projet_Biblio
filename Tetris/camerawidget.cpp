#include "camerawidget.h"

using namespace cv;
CameraWidget::CameraWidget(QLabel* label, QWidget *parent) : QWidget (parent)
{
    cap.open(0);
    labelCam = label;
    play_ = false;
    detector = FistDetection();
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
        while (waitKey(5)<0)
        {

            Mat frame;
            // Get frame
            cap >> frame;
            if (detector.loadCascade()){
                Movment mvmd = detector.detection(frame);
                emit tryMoveCam(mvmd);
                frame = detector.getDisplayFrame();
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
