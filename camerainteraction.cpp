#include "camerainteraction.h"
#include <QDebug>
#include <QImage>
#include <QPixmap>

CameraInteraction::CameraInteraction(QWidget *parent) : QWidget(parent)
{
    int frameWidth=320;
    int frameHeight=240;//240
    int subImageWidth=60;
    int subImageHeight=60;
    Rect rect((frameWidth-subImageWidth)/2,frameHeight/2+(frameHeight/2-subImageHeight)/2,subImageWidth,subImageHeight);
    Point p1(rect.x+subImageWidth/2,rect.y+subImageHeight/2);
    Point p2;
    this->p1= p1;
    this->p2 = p2;
    cap.open(0);

    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);
    // Get frame1
    cap >> frame1;
    // Mirror effect
    cv::flip(frame1,frame1,1);

    Mat(frame1,rect).copyTo(frameRect1);

    this->rect = rect;

}


void CameraInteraction::displayCamera(QLabel *label){
    if(!cap.isOpened())  // check if we succeeded
    {
        qDebug()<<"Error openning the default camera"<<endl;

    }


    cap >> frame2;
    // Mirror effect
    cvtColor(frame2,frame2, CV_BGR2RGB);
    cv::flip(frame2,frame2,1);
    Mat(frame2,rect).copyTo(frameRect2);

    // Compute optical flow
    //float start = (float)getTickCount();
//    calcOpticalFlowSF(frameRect1, frameRect2,
//                      flow,
//                      3, 2, 4, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10);

    float um,vm;
//    calc_mean(flow,um,vm);
//    //if((um>2 || um <-1) ){
////        printf("um: %lf\t", um);
////        printf("vm: %lf\n", vm);
//        if(um>0.5){
//            //myball->moveBy(10,0);
//            //myball->setPos(myball->x(), myball->y());
//        }else if(um<-0.5){
//            //myball->moveBy(-10,0);
//        }

    //}

    // Draw green rectangle and mean vector
    rectangle(frame2,rect,Scalar( 0, 255, 0),2);
    p2.x=p1.x+4*um;
    p2.y=p1.y+4*vm;
    line(frame2,p1,p2,Scalar(255,255,255),2);

    QImage img;
    QPixmap pixel;
    img= QImage((const unsigned char*) (frame2.data), frame2.cols, frame2.rows, frame2.step, QImage::Format_RGB888);
    pixel = QPixmap::fromImage(img);
    label->setPixmap(pixel);

    swap(frameRect1,frameRect2);

}


void CameraInteraction::detectHand(){

}

bool CameraInteraction::isFlowCorrect(float u) {
  return !cvIsNaN(u) && (fabs(u) < 1e9);
}

void CameraInteraction::calc_mean(Mat flow1,float &um, float &vm) {
  float sumu = 0;
  float sumv = 0;
  int counter = 0;
  const int rows = flow1.rows;
  const int cols = flow1.cols;

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      Vec2f flow1_at_point = flow1.at<Vec2f>(y, x);

      float u1 = flow1_at_point[0];
      float v1 = flow1_at_point[1];

      if (isFlowCorrect(u1) && isFlowCorrect(v1)) {
        sumu += u1;
        sumv += v1;
        counter++;
      }
    }
  }
  um=sumu/(1e-9 + counter);
  vm=sumv/(1e-9 + counter);
 }
