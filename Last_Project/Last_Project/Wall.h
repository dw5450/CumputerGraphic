#ifndef __WALL_H__
#define __WALL_H__
#include "MyStructs.h"
#include "MyFunction.h"
#include<glut.h>
#include<iostream>
#include<math.h>
#include<Windows.h>


class Wall
{
private:
	Point3d Pos;
	Point3d Size;
	HitBox Hitbox;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장핛 변수
	GLuint textures[1]; // 텍스처 이름
	void _drawWallFace(Point3d vertax_pos[], int vertax[], int vertax_num, bool outer_ctr);
	void _drawWall(double size);
	

public:
	Wall();
	Wall(Point3d _Pos, Point3d _Size);
	void insertPos(Point3d _Pos);
	void insertSize(Point3d _Size);
	HitBox returnHitBox();
	void draw();


};

#endif //#ifndef __WALL_H__