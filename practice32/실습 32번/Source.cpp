

#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<Windows.h>
#include<list>
#include<algorithm>
#include <stdio.h> // ��� ���� ����
#include <windows.h> // ��Ʈ�� ���� ���� �ڷ� ����

#define PI   3.14159265359

using namespace std;

//�ʿ��� ����ü ����
struct Point3d
{
	double x = 0;
	double y = 0;
	double z = 0;

	void insert(double X, double Y, double Z){
		x = X, y = Y, z = Z;
	}
};


//�ʿ��� ���� ����

double CameraXangle;            //x�� ����
double CameraYangle;            //y�� ����
double CameraZangle;            //z�� ����

double ViewingX;
double ViewingY;
double ViewingZ;

GLubyte *pBytes; // �����͸� ����ų ������
GLuint textures[1];
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

//�۷ι� ���� ������ ����
GLfloat GlobalAmbientLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };

//���� 0 ������ ����
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat DiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0f };
GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos0[] = { 0.0, 0, 0, 1.0 };

//�÷� ������ ����
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//�ʿ��� �Լ� ����



//���� �׸��� �Լ�
void drawFace(Point3d vertax_pos[], Point3d vertax_color[], int vertax[], int vertax_num, bool outer_ctr)         //������ ��� �� ��ǥ, ������ ��� �� ����, ���� ���� �� index, ���� ���� �� ����, ���� ���� ����  
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
		-(vector_A.x * vector_B.z - vector_A.z * vector_B.x),
		vector_A.x * vector_B.y - vector_A.y * vector_B.x);


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
		for (int j = 0; j < 100; j++)
			if (vertax[i] == j)
			{
				glColor3f(vertax_color[j].x, vertax_color[i].y, vertax_color[i].z);
				glVertex3d(vertax_pos[j].x, vertax_pos[j].y, vertax_pos[j].z);
				break;
			}
	}

	glEnd();
}
//need_fix
//�Ƕ�̵带 ������ �ִ� �Լ�
void drawPramid(Point3d pramid_dots_pos[5], Point3d pramid_dots_color[5], bool outer_ctr)//�Ƕ�̵� �� ��ġ 5��, �Ƕ�̵� �� ���� 5��, ���� ���� ����
{
	int front_face[] = { 0, 1, 4 };      //���� ��
	int left_face[] = { 0, 2, 1 };      //���� ��
	int back_face[] = { 0, 3, 2 };      //���� �� 
	int right_face[] = { 0, 4, 3 };      //������ ��
	int bottom_face[] = { 1, 4, 3, 2 };   //�ظ�


	drawFace(pramid_dots_pos, pramid_dots_color, front_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, left_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, back_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, right_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, bottom_face, 4, outer_ctr);

}
//need_fix_end


//���� ����� ���� ���� �Լ�
double getRadian(double _num)         //���� ���� return ������ ���Ȱ�
{
	return _num * (PI / 180);
}

//���� ��ġ�� ���� �׷��ִ� �Լ�
void drawRotate(double _r){            //���� ������ �Է� 
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 120; ++i){
		glVertex2f(_r * cos(3 * i * (PI / 180)), _r * sin(3 * i * (PI / 180)));
	}
	glEnd();
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fopen_s(&fp, filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	cout << ">" <<endl;
	// ������ BMP �������� Ȯ������.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� ������ ����.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
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

///ȭ�� ��Ʈ���� ���� �⺻ �Լ� ����
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
double getRadian(double _num);

void initialize()

{
	CameraXangle = 0;            //ī�޶� x�� ����
	CameraYangle = 0;            //ī�޶� y�� ����
	CameraZangle = 0;            //ī�޶� z�� ����

	ViewingX = 0;               //ī�޶� x�� ��ġ
	ViewingY = 0;               //ī�޶� y�� ��ġ
	ViewingZ = -10;               //ī�޶� z�� ��ġ

	GLubyte *m_bitmap;
	BITMAPINFO *m_bitInfo;
	GLfloat xoffset, yoffset;
	xoffset = 1;
	yoffset = 1;
	GLfloat xscale = 2.0, yscale = 2.0;
	m_bitmap = LoadDIBitmap("banana.BMP", &m_bitInfo);
	glRasterPos2f(xoffset, yoffset);
	glPixelZoom(xscale, yscale);
	glDrawPixels(179, 158, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap);
	
	
}

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 0); //    �������� ��ġ���� 
	glutInitWindowSize(700, 700); // �������� ũ�� ���� 
	glutCreateWindow("��ǻ�� �׷��� �⺻ �ڵ� by 2014180026"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �Լ��� ����
	glutMouseFunc(Mouse); // �ܼ� ���콺 �Է� �Լ��� ����
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ���� 

	initialize();

	glutMainLoop();

}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	//���� ��ȯ : ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);               // ���� ������ ����ϴ� ���
	gluPerspective(60.0, 1.0, 1.0, 1000.0);                     // ���� ������ ����ϴ� ���
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);      // ���� ������ ����ϴ� ���

	glPushMatrix();
	glTranslated(ViewingX, ViewingY, ViewingZ);
	glRotated(CameraXangle, 1.0, 0.0, 0.0);
	glRotated(CameraYangle, 0.0, 1.0, 0.0);
	glRotated(CameraZangle, 0.0, 0.0, 1.0);


	//�𵨸� ��ȯ : �� ��ġ ����
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // ������ ������ ��ü�� ĥ�ϱ�, ���� ����


	//���� ȿ�� ����
	glEnable(GL_LIGHTING);                                    //���� ��� ����
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbientLight);         //���� ���� �� ����

	//��ü �� ȿ�� �Ӽ� ����
	glEnable(GL_COLOR_MATERIAL);                              //�÷� Ʈ��ŷ ����(glColor3f��� ����)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //���� �Ӽ� ����(��ü �� ȿ�� ����)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //���̶���Ʈ ����
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //���̶���Ʈ ���
	glShadeModel(GL_SMOOTH);                                 //�ε巯�� ���̵�

	//���� ����, �ø� ����
	glEnable(GL_DEPTH_TEST);                                 //���� ���� 
	//glEnable(GL_CULL_FACE);                                 //�ø�
	//glFrontFace(GL_CCW);                                    //�ո� -> ccw(�ݽð� ����) ����

	glPushMatrix();

	//���� 0 ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);

	//����0 on
	glEnable(GL_LIGHT0);


	//x��   ������
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(1, 0, 0);
	glEnd();

	//y��   �ʷϻ�
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 1, 0);
	glEnd();


	//z��   //�Ķ���
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 1);
	glEnd();


	//�عٴ�  //�Ķ���
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(0.0, -4, 0.0);
	glScaled(1.0, 0.01, 1.0);

	glutSolidCube(10);

	glPopMatrix();


	// 6���� �̹��� �ؽ�ó ������ ����.
	//glGenTextures(1, textures);
	//�ؽ�ó�� ��ü�� ��������. --- (1)
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	////�̹��� �ε��� ����. --- (2)
	//pBytes = LoadDIBitmap("banana.BMP", &info);


	////�ؽ�ó ���� ���Ǹ� ����. --- (3)

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 179, 158, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);


	////�ؽ�ó �Ķ���� ���� --- (4)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//// ������ n-1���� �ؽ�ó���� (1) ~ (4)������ ������ �����Ͽ� �ؽ�ó�� ��������.
	//// �ؽ�ó ��� ����
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	//// �ؽ�ó ���� �R��ȭ
	//glEnable(GL_TEXTURE_2D);
	// �ؽ�ó�� ��ü�� ����
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
		glVertex3d(-1, -1, 0);
		glVertex3d(-1, 1, 0);
		glVertex3d(1, 1, 0);
		glVertex3d(1, -1, 0);
	glEnd();



	glPopMatrix();

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{


	glViewport(0, 0, w, h);
	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ�


	//glOrtho(SceneInit_x, SceneEnd_x, SceneInit_y, SceneEnd_y, -1.0, 1.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{

	if (key == '<' || key == ',')
		CameraYangle += 1.0;
	else if (key == '>' || key == '.')
		CameraYangle -= 1.0;


	else if (key == 'i')
		initialize();

	cout << "(" << ViewingX << ", " << ViewingY << ", " << ViewingZ << ")" << endl;

	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

GLvoid Mouse(int button, int state, int x, int y)
{




	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}