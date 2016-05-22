#ifndef CAMERAINTERACTION_H
#define CAMERAINTERACTION_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <algorithm>
#include <vector>
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class CameraInteraction : public QWidget
{
    Q_OBJECT
public:
    explicit CameraInteraction(QWidget *parent = 0);
    void displayCamera(QLabel *label);
    void detectHand();

    Mat Testmm(Mat frame);
    double dist(Point x,Point y);
    pair<Point,double> circleFromPoints(Point p1, Point p2, Point p3);


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


    Rect            rectRoi;
    Rect            rectRoiRech; //Rectangle de recherche.
    Point           posrectRoiRech;

    Mat             templ;

    Mat back;
    Mat fore;
    int backgroundFrame=500;
    vector<pair<Point,double> > palm_centers;
    BackgroundSubtractorMOG2 bg;

};

#endif // CAMERAINTERACTION_H
