#ifndef CLAWINTERACTION_H
#define CLAWINTERACTION_H

#include <QObject>
#include <QWidget>
#include <QGLWidget>
#include "ballrandom.h"

class ClawInteraction : public QGLWidget
{
    Q_OBJECT
public:
    explicit ClawInteraction(QWidget *parent =0);

    ~ClawInteraction();

    void draw();
    void moveBall(double posX=5.0, double posY=5.0, double posZ=1.0, int nbPas=100);
    BallRandom &getBall(){return ballR;}


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void loadGLTexture();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);



public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    GLuint m_texture[1];
   void sphere(int lats, int longs, float r);
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    BallRandom ballR;
};

#endif // CLAWINTERACTION_H
