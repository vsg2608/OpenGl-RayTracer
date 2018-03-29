#include<GL/gl.h>

void drawPoint(float x, float y, float r, float g, float b){
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
}
