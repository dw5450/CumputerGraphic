#include<iostream>
#include "Wall.h"
#include "MyStructs.h"
#include "MyFunction.h"
#include "MyInclude.h"

Wall::Wall()
{
	glGenTextures(1, textures);
	//텍스처와 객체를 결합핚다. --- (1)
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//이미지 로딩을 핚다. --- (2)
	pBytes = LoadDIBitmap("wall.BMP", &info);
	if (pBytes == NULL)
		printf("null\n");
	else
		printf("read\n");
}
Wall::Wall(Point3d _Pos, Point3d _Size) : Pos(_Pos), Size(_Size)
{ 

	glGenTextures(1, textures);
	//텍스처와 객체를 결합핚다. --- (1)
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//이미지 로딩을 핚다. --- (2)
	pBytes = LoadDIBitmap("wall.BMP", &info);
	if (pBytes == NULL)
		printf("null\n");
	else
		printf("read\n");

}

void Wall::_drawWallFace(Point3d vertax_pos[], int vertax[], int vertax_num, bool outer_ctr)
{
	Point3d vector_A;
	vector_A.insert(vertax_pos[vertax[0]].x - vertax_pos[vertax[1]].x,
		vertax_pos[vertax[0]].y - vertax_pos[vertax[1]].y,
		vertax_pos[vertax[0]].z - vertax_pos[vertax[1]].z);

	Point3d vector_B;
	vector_B.insert(vertax_pos[vertax[2]].x - vertax_pos[vertax[1]].x,
		vertax_pos[vertax[2]].y - vertax_pos[vertax[1]].y,
		vertax_pos[vertax[2]].z - vertax_pos[vertax[1]].z);

	Point3d outer;
	outer.insert(vector_A.y * vector_B.z - vector_A.z * vector_B.y,
		-(vector_A.x *  vector_B.z - vector_A.z *  vector_B.x),
		vector_A.x *  vector_B.y - vector_A.y *  vector_B.x);

	glBegin(GL_QUADS);

	//법선 벡터 설정

	if (outer_ctr == true)
		glNormal3f(outer.x, outer.y, outer.z);
	//면 그리기
	int cnt = 0;
	for (int i = 0; i < vertax_num; i++)
	{
		for (int j = 0; j < 8; j++)
			if (vertax[i] == j)
			{
				if (cnt == 0) glTexCoord2d(0.0f, 0.0f);

				if (cnt == 1) glTexCoord2d(0.0f, 1.0f);

				if (cnt == 2) glTexCoord2d(1.0f, 1.0f);

				if (cnt == 3) glTexCoord2d(1.0f, 0.0f);

				glVertex3d(vertax_pos[j].x, vertax_pos[j].y, vertax_pos[j].z);
				cnt++;
				break;
			}
	}

	glDisable(GL_TEXTURE_2D);
	glEnd();

}

void Wall::_drawWall(double size)
{
	//텍스처 설정 정의를 핚다. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	// 텍스처 파라미터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	Point3d dots[8];
	dots[0].insert(-(size / 2), (size / 2), (size / 2));
	dots[1].insert((size / 2), (size / 2), (size / 2));
	dots[2].insert((size / 2), (size / 2), -(size / 2));
	dots[3].insert(-(size / 2), (size / 2), -(size / 2));
	dots[4].insert(-(size / 2), -(size / 2), (size / 2));
	dots[5].insert((size / 2), -(size / 2), (size / 2));
	dots[6].insert((size / 2), -(size / 2), -(size / 2));
	dots[7].insert(-(size / 2), -(size / 2), -(size / 2));

	int up_vertax[] = { 0, 1, 2, 3 };
	_drawWallFace(dots, up_vertax, 4, 1);

	int front_vertax[] = { 0, 4, 5, 1 };
	_drawWallFace(dots, front_vertax, 4, 1);

	int right_vertax[] = { 1, 5, 6, 2 };
	_drawWallFace(dots, right_vertax, 4, 1);

	int back_vertax[] = { 2, 6, 7, 3 };
	_drawWallFace(dots, back_vertax, 4, 1);

	int left_vertax[] = { 3, 7, 4, 0 };
	_drawWallFace(dots, left_vertax, 4, 1);

	int down_vertax[] = { 4, 7, 6, 5 };
	_drawWallFace(dots, down_vertax, 4, 1);

	glDisable(GL_TEXTURE_2D);
}


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
		_drawWall(1);
	glPopMatrix();

}




