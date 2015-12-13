#ifndef __ITEM_H__
#define __ITEM_H__
#include "MyStructs.h"


class Item
{
private:
	Point3d Pos;
	Point3d Size;
	HitBox Hitbox;

public:
	Item(){};
	Item(Point3d _Pos, Point3d _Size) : Pos(_Pos), Size(_Size){ Hitbox.insert(Pos, Size); }
	void insertPos(Point3d _Pos);
	void insertSize(Point3d _Size);
	HitBox returnHitBox();
	void draw();


};
#endif //#ifndef Item