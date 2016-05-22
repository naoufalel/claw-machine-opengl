#include "camerainteraction.h"
#include <QDebug>
#include <QImage>
#include <QPixmap>

CameraInteraction::CameraInteraction(QWidget *parent) : QWidget(parent)
{
    int frameWidth=800;
    int frameHeight=340;//240
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

    bg.set("nmixtures",3);
    bg.set("detectShadows",false);

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


    //frame2 = Testmm(frame2);
    Mat(frame2,rect).copyTo(frameRect2);

    // Compute optical flow
    float start = (float)getTickCount();
    calcOpticalFlowSF(frameRect1, frameRect2,
                      flow,
                      3, 2, 4, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10);

    float um,vm;
    //calc_mean(flow,um,vm);
//    if((um>2 || um <-1) ){
//////        printf("um: %lf\t", um);
//////        printf("vm: %lf\n", vm);
//        if(um>0.5){
////            //myball->moveBy(10,0);
////            //myball->setPos(myball->x(), myball->y());
//        }else if(um<-0.5){
////            //myball->moveBy(-10,0);
//        }

//    }

    // Draw green rectangle and mean vector
    rectangle(frame2,rect,Scalar( 0, 255, 0),4);
    p2.x=p1.x+4*um;
    p2.y=p1.y+4*vm;
    line(frame2,p1,p2,Scalar(255,255,255),2);



    QImage img;
    QPixmap pixel;
    img= QImage((const unsigned char*) (frame2.data), frame2.cols, frame2.rows, frame2.step, QImage::Format_RGB888);
    pixel = QPixmap::fromImage(img);
    label->setPixmap(pixel);


            //resize(tst, tst, Size(480, 340));

    //swap(frameRect1,frameRect2);
    //detectHand();

}

double CameraInteraction::dist(Point x,Point y)
{
    return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);
}

pair<Point,double> CameraInteraction::circleFromPoints(Point p1, Point p2, Point p3)
{
    double offset = pow(p2.x,2) +pow(p2.y,2);
    double bc =   ( pow(p1.x,2) + pow(p1.y,2) - offset )/2.0;
    double cd =   (offset - pow(p3.x, 2) - pow(p3.y, 2))/2.0;
    double det =  (p1.x - p2.x) * (p2.y - p3.y) - (p2.x - p3.x)* (p1.y - p2.y);
    double TOL = 0.0000001;
    if (abs(det) < TOL) { cout<<"POINTS TOO CLOSE"<<endl;return make_pair(Point(0,0),0); }

    double idet = 1/det;
    double centerx =  (bc * (p2.y - p3.y) - cd * (p1.y - p2.y)) * idet;
    double centery =  (cd * (p1.x - p2.x) - bc * (p2.x - p3.x)) * idet;
    double radius = sqrt( pow(p2.x - centerx,2) + pow(p2.y-centery,2));

    return make_pair(Point(centerx,centery),radius);
}


Mat CameraInteraction::Testmm(Mat frame){




            vector<vector<Point> > contours;


            //Update the current background model and get the foreground
            if(backgroundFrame>0)
            {bg.operator ()(frame,fore);backgroundFrame--;}
            else
            {bg.operator()(frame,fore,0);}

            //Get background image to display it
            bg.getBackgroundImage(back);


            //Enhance edges in the foreground by applying erosion and dilation
            erode(fore,fore,Mat());
            dilate(fore,fore,Mat());


            //Find the contours in the foreground
            findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
            for(int i=0;i<contours.size();i++)
                //Ignore all small insignificant areas
                if(contourArea(contours[i])>=5000)
                {
                    //Draw contour
                    vector<vector<Point> > tcontours;
                    tcontours.push_back(contours[i]);
                    drawContours(frame,tcontours,-1,cv::Scalar(0,0,255),2);

                    //Detect Hull in current contour
                    vector<vector<Point> > hulls(1);
                    vector<vector<int> > hullsI(1);
                    convexHull(Mat(tcontours[0]),hulls[0],false);
                    convexHull(Mat(tcontours[0]),hullsI[0],false);
                    drawContours(frame,hulls,-1,cv::Scalar(0,255,0),2);

                    //Find minimum area rectangle to enclose hand
                    RotatedRect rect=minAreaRect(Mat(tcontours[0]));

                    //Find Convex Defects
                    vector<Vec4i> defects;
                    if(hullsI[0].size()>0)
                    {
                        Point2f rect_points[4]; rect.points( rect_points );
                        for( int j = 0; j < 4; j++ )
                            line( frame, rect_points[j], rect_points[(j+1)%4], Scalar(255,0,0), 1, 8 );
                        Point rough_palm_center;
                        convexityDefects(tcontours[0], hullsI[0], defects);
                        if(defects.size()>=3)
                        {
                            vector<Point> palm_points;
                            for(int j=0;j<defects.size();j++)
                            {
                                int startidx=defects[j][0]; Point ptStart( tcontours[0][startidx] );
                                int endidx=defects[j][1]; Point ptEnd( tcontours[0][endidx] );
                                int faridx=defects[j][2]; Point ptFar( tcontours[0][faridx] );
                                //Sum up all the hull and defect points to compute average
                                rough_palm_center+=ptFar+ptStart+ptEnd;
                                palm_points.push_back(ptFar);
                                palm_points.push_back(ptStart);
                                palm_points.push_back(ptEnd);
                            }

                            //Get palm center by 1st getting the average of all defect points, this is the rough palm center,
                            //Then U chose the closest 3 points ang get the circle radius and center formed from them which is the palm center.
                            rough_palm_center.x/=defects.size()*3;
                            rough_palm_center.y/=defects.size()*3;
                            Point closest_pt=palm_points[0];
                            vector<pair<double,int> > distvec;
                            for(int i=0;i<palm_points.size();i++)
                                distvec.push_back(make_pair(dist(rough_palm_center,palm_points[i]),i));
                            sort(distvec.begin(),distvec.end());

                            //Keep choosing 3 points till you find a circle with a valid radius
                            //As there is a high chance that the closes points might be in a linear line or too close that it forms a very large circle
                            pair<Point,double> soln_circle;
                            for(int i=0;i+2<distvec.size();i++)
                            {
                                Point p1=palm_points[distvec[i+0].second];
                                Point p2=palm_points[distvec[i+1].second];
                                Point p3=palm_points[distvec[i+2].second];
                                soln_circle=circleFromPoints(p1,p2,p3);//Final palm center,radius
                                if(soln_circle.second!=0)
                                    break;
                            }

                            //Find avg palm centers for the last few frames to stabilize its centers, also find the avg radius
                            palm_centers.push_back(soln_circle);
                            if(palm_centers.size()>10)
                                palm_centers.erase(palm_centers.begin());

                            Point palm_center;
                            double radius=0;
                            for(int i=0;i<palm_centers.size();i++)
                            {
                                palm_center+=palm_centers[i].first;
                                radius+=palm_centers[i].second;
                            }
                            palm_center.x/=palm_centers.size();
                            palm_center.y/=palm_centers.size();
                            radius/=palm_centers.size();

                            //Draw the palm center and the palm circle
                            //The size of the palm gives the depth of the hand
                            circle(frame,palm_center,5,Scalar(144,144,255),3);
                            circle(frame,palm_center,radius,Scalar(144,144,255),2);

                            //Detect fingers by finding points that form an almost isosceles triangle with certain thesholds
                            int no_of_fingers=0;
                            for(int j=0;j<defects.size();j++)
                            {
                                int startidx=defects[j][0]; Point ptStart( tcontours[0][startidx] );
                                int endidx=defects[j][1]; Point ptEnd( tcontours[0][endidx] );
                                int faridx=defects[j][2]; Point ptFar( tcontours[0][faridx] );
                                //X o--------------------------o Y
                                double Xdist=sqrt(dist(palm_center,ptFar));
                                double Ydist=sqrt(dist(palm_center,ptStart));
                                double length=sqrt(dist(ptFar,ptStart));

                                double retLength=sqrt(dist(ptEnd,ptFar));
                                //Play with these thresholds to improve performance
                                if(length<=3*radius&&Ydist>=0.4*radius&&length>=10&&retLength>=10&&max(length,retLength)/min(length,retLength)>=0.8)
                                    if(min(Xdist,Ydist)/max(Xdist,Ydist)<=0.8)
                                    {
                                        if((Xdist>=0.1*radius&&Xdist<=1.3*radius&&Xdist<Ydist)||(Ydist>=0.1*radius&&Ydist<=1.3*radius&&Xdist>Ydist))
                                            line( frame, ptEnd, ptFar, Scalar(0,255,0), 1 ),no_of_fingers++;
                                    }


                            }

                            no_of_fingers=min(5,no_of_fingers);
                            qDebug()<<"NO OF FINGERS: "<<no_of_fingers;
                            //mouseTo(palm_center.x,palm_center.y);//Move the cursor corresponding to the palm
                            if(no_of_fingers<4)//If no of fingers is <4 , click , else release
//                                mouseClick();
                                qDebug()<<"Test";
                            else
//                                mouseRelease();
                                qDebug()<<"Hola";

                        }
                    }

                }
            if(backgroundFrame>0)
                putText(frame, "Recording Background", cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
//            imshow("Framekj",frame);
//            imshow("Background",back);
return frame;

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
