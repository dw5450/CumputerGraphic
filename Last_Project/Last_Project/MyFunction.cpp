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

	//���� ���� ����

	if (outer_ctr == true)
		glNormal3f(outer.x, outer.y, outer.z);
	//�� �׸���
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

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	//if (( fopen( fpf, ilename, "rb")) == NULL)
	//	return NULL;
	fopen_s(&fp, filename, "rb");
	//printf("1\n");
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	//printf("2\n");
	// ������ BMP �������� Ȯ������.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	//printf("3\n");
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� ������ ����.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	//printf("4\n");
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	//printf("5\n");
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� ��������.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� ��������.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}



