#include "clawinteraction.h"

#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/gl.h>

ClawInteraction::ClawInteraction(QWidget *parent):
    QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    zTra = 0;
}

ClawInteraction::~ClawInteraction(){

}



QSize ClawInteraction::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize ClawInteraction::sizeHint() const
{
    return QSize(800, 800);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void ClawInteraction::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void ClawInteraction::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void ClawInteraction::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void ClawInteraction::initializeGL()
{
    qglClearColor(Qt::white);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);

//    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glAlphaFunc ( GL_GREATER, 0.1 ) ;
    glEnable ( GL_ALPHA_TEST ) ;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



}

void ClawInteraction::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();

}

void ClawInteraction::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-15, +15, -15, +20, -15, 15);
//#else
//    glOrtho(-15, +15, -15, +20, -30, 30);
//#endif
    gluPerspective(70,((float)width/(float)height),0.01,30);
    glMatrixMode(GL_MODELVIEW);
}

void ClawInteraction::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ClawInteraction::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}


// Zoom
void ClawInteraction::setZTranslation(int dist)
{
    zTra += dist;
    emit zTransChanged(dist);
    updateGL();
}


void ClawInteraction::wheelEvent(QWheelEvent *event)
{
    setZTranslation(event->delta()/16);
}


void ClawInteraction::loadGLTexture()
{

    QImage image(":/Images/Bois.jpg");
    image = image.convertToFormat(QImage::Format_RGB888);
    image = image.mirrored();
    glGenTextures(1, &m_texture[0]);
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_REPEAT);
}


void ClawInteraction::draw()
{
    randomBallDraw();
    base.draw();
}

void ClawInteraction::randomBallDraw(){
    int atBaseLevel = - base.getLimit() - ballR.getRadius();
    glPushMatrix();
        glTranslatef(0,atBaseLevel,0);
            ballR.drawBall();
    glPopMatrix();
}


void ClawInteraction::moveBall(double posX, double posY, double posZ, int nbPas){
    double initX=ballR.getX();
    double initY=ballR.getY();
    double initZ=ballR.getZ();
    double tmpX;
    double tmpY;
    double tmpZ;
    for (int i=0; i<nbPas+1; i++)
    {
        tmpX=(initX*(nbPas-i)+(posX*i))/nbPas;
        tmpY=(initY*(nbPas-i)+(posY*i))/nbPas;
        tmpZ=(initZ*(nbPas-i)+(posZ*i))/nbPas;
        ballR.setX(tmpX);
        ballR.setY(tmpY);
        ballR.setZ(tmpZ);
        ballR.drawBall();
        //qDebug()<<i <<"   x: "<<tmpX<<" y: "<<tmpY;
        updateGL();
        //QThread::usleep(100);
        //qDebug()<<"balle :"<<(int)laBalle.getX()<<" "<<(int)laBalle.getY();
        //qDebug()<<"cible :"<<(int)lArene.getXCible()<<" "<<(int)lArene.getYCible();
//        if((int)laBalle.getX()==(int)lArene.getXCible() && (int)laBalle.getY()==(int)lArene.getYCible())
//        {
//            qDebug()<<"BALLE SUR CIBLE";
//            emit finPartie();
//            brasAttrapeBalle();
//            reinitJeu();

//        }
    }
}


