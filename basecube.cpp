#include "basecube.h"

BaseCube::BaseCube(QObject *parent) : QObject(parent)
{
    areteLength = 2;
    arete = areteLength/2.85989;
}

void BaseCube::draw(){

    drawExit();


    glPushMatrix();
    glScalef(2,2,2);
    glBegin(GL_QUADS);
    // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out
          glColor4f(0.0f, 0.0f, 1.0f,0.15);     // Green
          glVertex3f( areteLength, areteLength, -areteLength);
          glVertex3f(-areteLength, areteLength, -areteLength);
          glVertex3f(-areteLength, areteLength, areteLength);
          glVertex3f( areteLength, areteLength, areteLength);

          // Bottom face (y = -1.0f)



          glColor4f(0.0f, 0.0f, 1.0f,0.15);     // Orange
          glVertex3f(areteLength,-areteLength,areteLength);
          glVertex3f(-areteLength,-areteLength,areteLength);
          glVertex3f(-areteLength,-areteLength,-areteLength);
          glVertex3f( areteLength,-areteLength,-areteLength);

          // Front face  (z = 1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.15);     // Red
          glVertex3f( areteLength,areteLength,areteLength);
          glVertex3f(-areteLength,areteLength,areteLength);
          glVertex3f(-areteLength,-areteLength,areteLength);
          glVertex3f( areteLength,-areteLength,areteLength);

          // Back face (z = -1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.15);    // Yellow
          glVertex3f( areteLength, -areteLength, -areteLength);
          glVertex3f(-areteLength,-areteLength,-areteLength);
          glVertex3f(-areteLength,areteLength,-areteLength);
          glVertex3f( areteLength,areteLength,-areteLength);

          // Left face (x = -1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.15);     // Blue
          glVertex3f( -areteLength, areteLength, areteLength);
          glVertex3f(-areteLength,areteLength,-areteLength);
          glVertex3f(-areteLength,-areteLength,-areteLength);
          glVertex3f( -areteLength,-areteLength,areteLength);

          // Right face (x = 1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.15);      // Magenta
          glVertex3f( areteLength, areteLength, -areteLength);
          glVertex3f(areteLength,areteLength,areteLength);
          glVertex3f(areteLength,-areteLength,areteLength);
          glVertex3f( areteLength,-areteLength,-areteLength);
       glEnd();
    glPopMatrix();


}

void BaseCube::drawExit(){
    glPushMatrix();
    glTranslatef(-areteLength- arete*1.85989, -areteLength - arete*1.85989, areteLength+arete*1.85989);
    glColor3f(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(arete,-arete,arete);
            glVertex3f(-arete,-arete,arete);
            glVertex3f(-arete,-arete,-arete);
            glVertex3f( arete,-arete,-arete);
        glEnd();
    glPopMatrix();
}
