#include "MyFunction.h"
#include<iostream>
#include<math.h>
#include <glut.h>


void drawFace(Point3d vertax_pos[], int vertax[], int vertax_num, bool outer_ctr)
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


	if (vertax_num == 3)
		glBegin(GL_TRIANGLES);
	else if (vertax_num == 4)
		glBegin(GL_QUADS);

	//법선 벡터 설정

	if (outer_ctr == true)
		glNormal3f(outer.x, outer.y, outer.z);
	//면 그리기
	for (int i = 0; i < vertax_num; i++)
	{
		for (int j = 0; j < 8; j++)
			if (vertax[i] == j)
			{
				glVertex3d(vertax_pos[j].x, vertax_pos[j].y, vertax_pos[j].z);
				break;
			}
	}

	glEnd();

}

void drawCube(double size)
{
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
	drawFace(dots, up_vertax, 4, 1);

	int front_vertax[] = { 0, 4, 5, 1 };
	drawFace(dots, front_vertax, 4, 1);

	int right_vertax[] = { 1, 5, 6, 2 };
	drawFace(dots, right_vertax, 4, 1);

	int back_vertax[] = { 3, 2, 6, 7 };
	drawFace(dots, back_vertax, 4, 1);

	int left_vertax[] = { 0, 3, 7, 4 };
	drawFace(dots, left_vertax, 4, 1);

	int down_vertax[] = { 4, 7, 6, 5 };
	drawFace(dots, down_vertax, 4, 1);


}
