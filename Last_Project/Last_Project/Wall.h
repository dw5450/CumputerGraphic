#ifndef __WALL_H__
#define __WALL_H__
#include "MyStructs.h"
#include "MyFunction.h"
#include<glut.h>

class Wall
{
private:
	Point3d Pos;
	Point3d Size;
	HitBox Hitbox;
	

public:
	Wall(){};
	Wall(Point3d _Pos, Point3d _Size) : Pos(_Pos), Size(_Size){ Hitbox.insert(Pos, Size); }
	void insertPos(Point3d _Pos);
	void insertSize(Point3d _Size);
	HitBox returnHitBox();
	void draw();


};

#endif //#ifndef __WALL_H__