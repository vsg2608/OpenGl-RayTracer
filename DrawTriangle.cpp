#include <windows.h>
#include <GL/gl.h>

// Function to draw triangle
void drawTriangle(){
    glColor3f(0.0f, 0.0f, 1.0f);     // Sets color| 3f method is used as it enables us to declare color in proportional range| f stands for float
    glBegin(GL_TRIANGLES);
    glVertex3f(-.75f, 0.0f, 0.0f);
    glVertex3f(.75f, 0.0f, 0.0f);
    glVertex3f(-0.3f, .75f, 0.0f);


    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
}
