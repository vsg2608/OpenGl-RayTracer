#include <windows.h>
#include <GL/gl.h>
#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

void drawHandle(HDC hDC);
void drawAll();
void drawTriangle();
void drawSquare();
void drawPoint(float x, float y, float r, float g, float b);
void SetColor();
float retCol(int i,int j,int k);
#endif // DRAW_H_INCLUDED
