#ifndef CAMERAINTERACTION_H
#define CAMERAINTERACTION_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QLabel>

#include "opencv2/opencv.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace cv;

class CameraInteraction : public QWidget
{
    Q_OBJECT
public:
    explicit CameraInteraction(QWidget *parent = 0);
    void displayCamera(QLabel *label);
    void detectAndTrackHand();
    bool isFlowCorrect(float u);
    void calc_mean(Mat flow1,float &um, float &vm);


signals:

public slots:


private:
    QTimer *timer;
    VideoCapture cap;
    Mat frame1;
    Mat frameRect1;
    Mat frame2;
    Mat flow;
    Mat frameRect2;
    Rect rect;
    Point p1;
    Point p2;

};

#endif // CAMERAINTERACTION_H
