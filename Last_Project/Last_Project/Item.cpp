#include "Item.h"
#include <glut.h>

void Item::insertPos(Point3d _Pos){ Pos = _Pos; }
void Item::insertSize(Point3d _Size)
{
	Size = _Size;
	Hitbox.insert(Pos, Size);
}
HitBox Item::returnHitBox() { return Hitbox; }


void Item::draw()
{
	glPushMatrix();
	glTranslated(Pos.x, Pos.y, Pos.z);
	glScaled(Size.x, Size.y, Size.z);
	glutSolidTeapot(5);
	glPopMatrix();

}


