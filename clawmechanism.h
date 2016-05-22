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

    const double getAngleToOpenCloseHand() {return this->angleToOpenCloseHand;}
    void setAngleToOpenCloseHand(double a){this->angleToOpenCloseHand = a;}

    const double getAngleWhenMovement() {return this->angleWhenMovement;}
    void setAngleWhenMovement(double a){this->angleWhenMovement = a;}


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
    double angleWhenMovement;


};

#endif // CLAWMECHANISM_H
