#include<iostream>
#include "Wall.h"
#include "MyStructs.h"
#include <glut.h>


void Wall::insertPos(Point3d _Pos){ Pos = _Pos; }
void Wall::insertSize(Point3d _Size)
{
	Size = _Size;
	Hitbox.insert(Pos, Size);
}
HitBox Wall::returnHitBox() { return Hitbox; }


void Wall::draw()
{
	glPushMatrix();
		glTranslated(Pos.x, Pos.y, Pos.z);
		glScaled(Size.x, Size.y, Size.z);
		drawCube(1);
	glPopMatrix();

}




