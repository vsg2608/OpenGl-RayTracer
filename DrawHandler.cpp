 #include <windows.h>
 #include <GL/gl.h>
 #include "Draw.h"

 void drawHandle(HDC hDC){
     /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();


            drawAll();

            glPopMatrix();
            glFlush();
            glFinish();

            SwapBuffers(hDC);


            Sleep (1);
 }
