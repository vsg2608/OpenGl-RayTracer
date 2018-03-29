#include <windows.h>
#include <GL/gl.h>
#include "Draw.h"
#include <stdio.h>
float image[500][500][3];

void drawAll(){
    SetColor();
    float wind_len = sizeof image / sizeof image[0];
    float wind_wid = sizeof image[0] / sizeof image[0][0];
    for(int i=0; i<wind_len; i++)
        for(int j=0; j<wind_wid; j++){
            if(true){
                image[i][j][0] = retCol(i,j,0);
                image[i][j][1] = retCol(i,j,1);
                image[i][j][2] = retCol(i,j,2);
            }
        }


    float x,y; //for coordinates
    float r,g,b; // for colors
    //printf("***\n");
    for(int i=0; i<wind_len; i++)
        for(int j=0; j<wind_wid; j++){
            r =image[i][j][0];
            g =image[i][j][1];
            b =image[i][j][2];
            x=2*i/wind_len-1;
            y=2*j/wind_wid-1;
            drawPoint(x,y,r,g,b);
        }
}
