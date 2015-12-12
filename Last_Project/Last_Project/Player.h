#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "MyStructs.h"

#define VIEWFRONT 0
#define VIEWRIGHT 90
#define VIEWBACK 180
#define VIEWLEFT 270



class Player
{
private:
	Point3d Eye;
	Point3d ViewPoint;
	Point3d oldEye;
	int HitBoxSize;
	int CameraTotalAngle = 0;
	int ViewMode = VIEWFRONT;

public:
	Player(){};
	Player(Point3d _Eye, Point3d _ViewPoint) : Eye(_Eye), ViewPoint(_ViewPoint){ HitBoxSize = 0; }
	void insertEye(Point3d _Eye);
	void insertViewPoint(Point3d _ViewPoint);
	Point3d returnEye();
	Point3d returnViewPoint();
	void Move(char key);
	void ChangeViewPoint(char key);
	bool CrushWithWall(HitBox WallHitBox);
	bool CrushWithEndPoint(HitBox EndPointHitBox);

};


#endif