#include "basecube.h"

BaseCube::BaseCube(QObject *parent) : QObject(parent)
{
    areteLength = 2;

}

void BaseCube::draw(){

    glPushMatrix();
    glScalef(2,2,2);
    glBegin(GL_QUADS);
    // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out
          glColor4f(0.0f, 0.0f, 1.0f,0.2);     // Green
          glVertex3f( areteLength, areteLength, -areteLength);
          glVertex3f(-areteLength, areteLength, -areteLength);
          glVertex3f(-areteLength, areteLength, areteLength);
          glVertex3f( areteLength, areteLength, areteLength);

          // Bottom face (y = -1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.2);     // Orange
          glVertex3f(areteLength,-areteLength,areteLength);
          glVertex3f(-areteLength,-areteLength,areteLength);
          glVertex3f(-areteLength,-areteLength,-areteLength);
          glVertex3f( areteLength,-areteLength,-areteLength);

          // Front face  (z = 1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.2);     // Red
          glVertex3f( areteLength,areteLength,areteLength);
          glVertex3f(-areteLength,areteLength,areteLength);
          glVertex3f(-areteLength,-areteLength,areteLength);
          glVertex3f( areteLength,-areteLength,areteLength);

          // Back face (z = -1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.2);    // Yellow
          glVertex3f( areteLength, -areteLength, -areteLength);
          glVertex3f(-areteLength,-areteLength,-areteLength);
          glVertex3f(-areteLength,areteLength,-areteLength);
          glVertex3f( areteLength,areteLength,-areteLength);

          // Left face (x = -1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.2);     // Blue
          glVertex3f( -areteLength, areteLength, areteLength);
          glVertex3f(-areteLength,areteLength,-areteLength);
          glVertex3f(-areteLength,-areteLength,-areteLength);
          glVertex3f( -areteLength,-areteLength,areteLength);

          // Right face (x = 1.0f)
          glColor4f(0.0f, 0.0f, 1.0f,0.2);      // Magenta
          glVertex3f( areteLength, areteLength, -areteLength);
          glVertex3f(areteLength,areteLength,areteLength);
          glVertex3f(areteLength,-areteLength,areteLength);
          glVertex3f( areteLength,-areteLength,-areteLength);
       glEnd();
    glPopMatrix();

}
