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
	GLubyte *pBytes; // �����͸� ����ų ������
	BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
	GLuint textures[1]; // �ؽ�ó �̸�
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