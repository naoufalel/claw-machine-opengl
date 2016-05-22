#ifndef BALLRANDOM_H
#define BALLRANDOM_H

#include <QObject>
#include <GL/glu.h>
#include <GL/gl.h>

class BallRandom : public QObject
{
    Q_OBJECT
public:
    explicit BallRandom(QObject *parent = 0);

    void drawBall();

    const double getX(){return x;}
    void setX(double x) {this->x = x;}

    const double getY() {return y;}
    void setY(double y){this->y = y;}

    const double getZ() {return z;}
    void setZ(double z){this->z = z;}



signals:

public slots:

private:
private:
    double x;
    double y;
    double z;
    float radius;
    GLUquadricObj *obj;
};

#endif // BALLRANDOM_H
