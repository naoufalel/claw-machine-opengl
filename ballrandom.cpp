#include "ballrandom.h"

BallRandom::BallRandom(QObject *parent) : QObject(parent)
{
    radius=1;
    x=0;
    y=0;
    z=0;

}


void BallRandom::drawBall(){

    glPushMatrix();
        obj = gluNewQuadric();
        glTranslatef(x,y,z);
        glColor3f(0,1,0);
        gluSphere(obj,radius,30,30);

    glPopMatrix();

}
