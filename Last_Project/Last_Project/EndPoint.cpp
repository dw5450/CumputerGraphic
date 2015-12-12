#include<iostream>
#include "EndPoint.h"
#include "MyStructs.h"
#include <glut.h>


void EndPoint::insertPos(Point3d _Pos){ Pos = _Pos; }
void EndPoint::insertSize(Point3d _Size)
{
	Size = _Size;
	Hitbox.insert(Pos, Size);
}
HitBox EndPoint::returnHitBox() { return Hitbox; }


void EndPoint::draw()
{
	glPushMatrix();
	glTranslated(Pos.x, Pos.y, Pos.z);
	glScaled(Size.x, Size.y, Size.z);
	glutSolidSphere(0.5, 16, 16);
	glPopMatrix();

}



