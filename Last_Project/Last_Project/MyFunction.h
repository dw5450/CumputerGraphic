#ifndef __MYFUNCTION_H__
#define	__MYFUNCTION_H__
#include "MyStructs.h"
#include<glut.h>
#include<iostream>
#include<math.h>
#include<Windows.h>



void drawFace(Point3d vertax_pos[], int vertax[], int vertax_num, bool outer_ctr);

void drawCube(double size);

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


#endif //#ifndef __MYFUNCTION_H__