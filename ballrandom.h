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

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);



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
