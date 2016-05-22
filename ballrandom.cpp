#include "ballrandom.h"

BallRandom::BallRandom(QObject *parent) : QObject(parent)
{
    radius=2;
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

double BallRandom::getX() const
{
    return x;
}

void BallRandom::setX(double value)
{
    x = value;
}
double BallRandom::getY() const
{
    return y;
}

void BallRandom::setY(double value)
{
    y = value;
}
double BallRandom::getZ() const
{
    return z;
}

void BallRandom::setZ(double value)
{
    z = value;
}

