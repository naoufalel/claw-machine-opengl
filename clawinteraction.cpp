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
    //x=0;
    //y=0;

    //ballR = new BallRandom();
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);



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

void ClawInteraction::sphere(int lats, int longs, float r)
{
    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = r*cos(lng);
            double y = r*sin(lng);
            glNormal3f(x * zr0, y * zr0, r*z0);
            glVertex3f(x * zr0, y * zr0, r*z0);
            glNormal3f(x * zr1, y * zr1, r*z1);
            glVertex3f(x * zr1, y * zr1, r*z1);
        }
        glEnd();
    }
}




/*void MyGLWidget::drawSphere(){
    // x^2 + y^2 = 49
 float x=moveX->move();
    glPushMatrix();
        glTranslatef(x,0,0);
        glColor3f(0,1,0);
        sphere(100, 100, 1.5);
    glPopMatrix();
}*/


void ClawInteraction::draw()
{

//   // x^2 + y^2 = 49
////    glPushMatrix();
////        glTranslatef(x,y,0);
////        glColor3f(0,1,0);
////        sphere(100, 100, 1.5);
////    glPopMatrix();
//    glPushMatrix();
//        glTranslatef(x+10,y+10,0);
//        glColor3f(0,1,0);
//        sphere(100, 100, 1.5);
//    glPopMatrix();

    ballR.drawBall();

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


void ClawInteraction::keyPressEvent(QKeyEvent *event){
//    if (event->key() == Qt::Key_Left)
//    {
//        yTrans -= 2;
//    }
//    if (event->key() == Qt::Key_Right)
//    {
//        yTrans += 2;
//    }
//    if (event->key() == Qt::Key_Up)
//    {
//        xTrans -= 2;
//    }
//    if (event->key() == Qt::Key_Down)
//    {
//        xTrans += 2;
//    }

//    if (event->key() == Qt::Key_8)
//    {
//        zTrans += 2;
//    }
//    if (event->key() == Qt::Key_2)
//    {
//        zTrans -= 2;
//    }
    if (event->key() == Qt::Key_D)
    {
//        this->deplacerBras(20,45,45);
        this->moveBall(10,0);
    }
    if (event->key() == Qt::Key_I)
    {
//        this->deplacerBras();
        this->moveBall();
    }
//    if (event->key() == Qt::Key_A)
//    {
//        this->brasAttrapeBalle();
//    }

//    if (event->key() == Qt::Key_Y)
//    {
//        lArene.positionnerCible();
//    }


    updateGL();
}
