#ifndef BASECUBE_H
#define BASECUBE_H

#include <QObject>
#include <GL/glu.h>
#include <GL/gl.h>

class BaseCube : public QObject
{
    Q_OBJECT
public:
    explicit BaseCube(QObject *parent = 0);
    void draw();

    void drawExit();

    int getLimit(){return this->areteLength;}
signals:

public slots:

private:

    int areteLength;
    double arete;
    GLUquadricObj *obj;


};

#endif // BASECUBE_H
