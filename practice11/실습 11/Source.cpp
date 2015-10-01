
//�ݽð� �������� ����ϸ鼭 ũ�Ⱑ ���ϴ� ���� ����
//
//
//
//
//���콺�� ������ ������ �簢�� �ƴϸ� �ﰢ���� ����



#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<Windows.h>
#include<list>
#include<algorithm>

#define PI	3.14159265359

#define SceneInit_x		-400.0
#define SceneInit_y		-300.0
#define SceneEnd_x		400.0
#define SceneEnd_y		300.0

#define Translate		215123
#define Rotate			215124
#define Scale			215125

#define triangle		216123
#define rectangle		216124

using namespace std;

//�ʿ��� ���� ����

struct ModleChange

{
	int type = NULL;
	double angle = NULL;
	double x = NULL;
	double y = NULL;
	double z = NULL;

	ModleChange(){}
	ModleChange(int Type, double Angle, double X, double Y, double Z)
		: type(Type), angle(Angle), x(X), y(Y), z(Z){}

	void InPut(int Type, double Angle, double X, double Y, double Z)
	{
		type = Type;
		angle = Angle;
		x = X;
		y = Y;
		z = Z;
	}
	
};



struct Point

{
	double x;
	double y;
};


	
bool Reset = false;
bool Quit = false;

Point Cp;

double SpinTriAngle = 0;
double TriScale = 1.1;

int shape = triangle;
int MoveType = 0;



list<ModleChange> ModleChangeList;

///ȭ�� ��Ʈ���� ���� �⺻ �Լ� ����
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
void ChangeDotsList();
double getRadian(double _num);

//���� ����� ���� ���� �Լ�

double getRadian(double _num)
{
	return _num * (PI / 180);
}
void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // 	�������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("�ǽ� 11"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �Լ��� ����
	glutMouseFunc(Mouse); // �ܼ� ���콺 �Է� �Լ��� ����
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ���� 
	if (!Quit)
		glutMainLoop();

}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	
	list<ModleChange>::iterator itor = ModleChangeList.begin();
	
	for (itor = ModleChangeList.begin(); itor != ModleChangeList.end(); itor++)
	{
		glPopMatrix();
	}
	ModleChangeList.clear();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);				// �׸��� ���� 'blue' ���� ����

	//GL_LINE�� �ȱ׷����� ��� �� �κ�, ���м�
	glBegin(GL_LINE_STRIP);
	{
		glVertex2i(0, SceneInit_x);
		glVertex2i(0, SceneEnd_y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	{
		glVertex2i(SceneInit_x, 0);
		glVertex2i(SceneEnd_x, 0);
	}
	glEnd();

	double TempAngle = 0;
	double TempR = 100;

	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < 360; i++)
		{
			glVertex2f(TempR * cos(getRadian(TempAngle)), TempR * sin(getRadian(TempAngle)));
			TempAngle++;
		}
	}
	glEnd();

	ModleChange TempModleChange;

	if (MoveType == 0)
	{
		TempModleChange.InPut(Rotate, SpinTriAngle, 0, 0, 1);
		ModleChangeList.push_back(TempModleChange);

		TempModleChange.InPut(Translate, 0, 0, 100, 0);
		ModleChangeList.push_back(TempModleChange);

		TempModleChange.InPut(Scale, 0, TriScale, TriScale, 0);
		ModleChangeList.push_back(TempModleChange);
	}

	else if (MoveType == 1)
	{
		TempModleChange.InPut(Translate, 0, Cp.x, Cp.y, 0);
		ModleChangeList.push_back(TempModleChange);

	}


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		for (itor = ModleChangeList.begin(); itor != ModleChangeList.end(); itor++)
		{
			if (itor->type == Translate)
				glTranslated(itor->x, itor->y, itor->z);

			else if (itor->type == Rotate)
				glRotated(itor->angle,itor->x, itor->y, itor->z);

			else if (itor->type == Scale)
				glScaled(itor->x, itor->y, itor->z);
		}

		if (shape == triangle)
		{
			glBegin(GL_POLYGON);

			glVertex2i(0, 20);
			glVertex2i(-15, -10);
			glVertex2i(15, -10);

			glEnd();
		}


		else if (shape == rectangle)
		{
			glBegin(GL_POLYGON);

			glVertex2i(15, 15);
			glVertex2i(-15, 15);
			glVertex2i(-15, -15);
			glVertex2i(15, -15);

			glEnd();
		}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(SceneInit_x, SceneEnd_x, SceneInit_y, SceneEnd_y, -1.0, 1.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{	
	ModleChangeList.clear();
	if (key == '1')
	{
		

	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (shape == rectangle)
		shape = triangle;
	else
		shape = rectangle;
	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{
	SpinTriAngle++;

	if ((int)SpinTriAngle % 5 == 0)
	{
		if (TriScale == 1.1)
			TriScale = 0.9;
		else if (TriScale == 0.9)
			TriScale = 1.1;
	}

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}

