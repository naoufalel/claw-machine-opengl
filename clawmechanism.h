#ifndef CLAWMECHANISM_H
#define CLAWMECHANISM_H

#include <QObject>

class ClawMechanism : public QObject
{
    Q_OBJECT
public:
    explicit ClawMechanism(QObject *parent = 0);

    void drawAll();

    const double getX(){return x;}
    void setX(double x) {this->x = x;}

    const double getY() {return y;}
    void setY(double y){this->y = y;}

    const double getZ() {return z;}
    void setZ(double z){this->z = z;}

    const double getAngleToOpenCloseHand() {return angleToOpenCloseHand;}
    void setZ(double a){this->angleToOpenCloseHand = a;}


signals:

public slots:


private:
    void drawFinger();
    void drawHand();
    void drawCord();

    double x;
    double y;
    double z;

    double angleToOpenCloseHand;


};

#endif // CLAWMECHANISM_H
