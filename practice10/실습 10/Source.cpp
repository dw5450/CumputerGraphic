//��ǥ�� �̵� �ǽ�
//
//
//
//
//S ���� ��� �׸�
//
//C �ڻ��� ��� �׸�
//
//P �������� �׸�
//
//Q �簢���� �׸�
//
//
//
//X ���������� �̵�
//
//x �������� �̵�
//
//Y ���� �̵�
//
//y ������ �̵�
//
//
//
//R ���� ���� ȸ��
//
//r ���� ���� ȸ��
//
//
//
//E ���� ���� ũ�� ����
//
//e ���� ���� ũ�� ����
//
//
//
//D ���� ���� ũ�� ����
//
//d ���� ���� ũ�� ����
//
//
//
//B sin->cos, cos->sin ��ȯ �ݺ� on
//
//b  sin->cos, cos->sin ��ȯ �ݺ� off
//
//
//
//I ����
//
//
//
//Q���α׷� ����
//
//
//
//
//


#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<Windows.h>
#include<list>
#include<algorithm>

#define PI	3.14159265359

#define DrawSin			205123
#define DrawCos			205124
#define DrawSpring		205125
#define DrawRectangle	205126

#define MoveLeft		210123
#define MoveRight		210124
#define MoveUp			210125
#define MoveDown		210126
#define Spin			210127
#define Expand			210128
#define DownScale		210129

#define SceneInit_x		-400.0
#define SceneInit_y		-300.0
#define SceneEnd_x		400.0
#define SceneEnd_y		300.0

using namespace std;

//�ʿ��� ���� ����

struct Point

{
	double x;
	double y;
};

Point CurCP;									//���� �߽� ��ǥ
int CurR;										//���� ������
int CurRDirection = 0;							//���� �������� �̵� ����
bool MoveROrder = false;
bool Reset = false;
bool Quit = false;
list<Point> Dots;								//������ ������ ����Ʈ;
int ShapeOrder;										//��ɾ� ������ ���� ����
list<int> RocationOrder;

bool Roatation;

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
	glutCreateWindow("�ǽ� 10"); // ������ ���� (������ �̸�) 
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'black' �� ���� 
	glClear( GL_COLOR_BUFFER_BIT ); // ������ ������ ��ü�� ĥ�ϱ�
	glMatrixMode(GL_MODELVIEW);
	
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);				// �׸��� ���� 'blue' ���� ����

	list<int>::iterator itor = RocationOrder.begin();
	for (itor = RocationOrder.begin(); itor != RocationOrder.end(); itor++)
	{
		glPopMatrix();
	}
	//���м� �漷�� ��
	glBegin(GL_LINES);
	{
		glVertex2i(0, SceneInit_x);
		glVertex2i(0, SceneEnd_y);
		glVertex2i(SceneInit_x, 0);
		glVertex2i(SceneEnd_x, 0);
	}
	glEnd();

	if (Reset)
	{
		ShapeOrder = NULL;
		RocationOrder.clear();
		Dots.clear();
		Reset = false;
	}
	else
	{
		glPushMatrix();
			for (itor = RocationOrder.begin(); itor != RocationOrder.end(); itor++)
			{
				if (*itor == MoveRight)
					glTranslatef(10, 0.0, 0.0);
				else if (*itor == MoveLeft)
					glTranslatef(-10, 0.0, 0.0);
				if (*itor == MoveUp)
					glTranslatef(0, 10.0, 0.0);
				else if (*itor == MoveDown)
					glTranslatef(0, -10.0, 0.0);
				else if (*itor == Spin)
					glRotatef(45, 0, 0, 1);
				else if (*itor == Expand)
					glScalef(1.10, 1.10, 0);
				else if (*itor == DownScale)
					glScalef(0.90, 0.90, 0);

			}

		glBegin(GL_LINE_STRIP);

		ChangeDotsList();
		list<Point>::iterator Potor = Dots.begin();
		float Blue = 1.0;
		float Red = 0.0;

		for (Potor = Dots.begin(); Potor != Dots.end(); Potor++)
		{
			glColor4f(Red, 0.0f, Blue, 1.0f);				// �׸��� ���� 'blue' ���� ����

			Blue -= 0.0007;
			Red += 0.0007;

			glVertex2i(Potor->x, Potor->y);
		}

		glEnd();
		Dots.clear();
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
	if (key == 'S')
	{
		CurR = 45;
		ShapeOrder = DrawSin;
	}
	else if (key == 'C')
	{
		CurR = 45;
		ShapeOrder = DrawCos;
	}
	else if (key == 'P')
		ShapeOrder = DrawSpring;
	else if (key == 'Q')
		ShapeOrder = DrawRectangle;


	else if (key == 'X')
	{
		if (Roatation == true)
			RocationOrder.push_front(MoveRight);
		else if (Roatation == false)
			RocationOrder.push_back(MoveRight);
	}
	else if (key == 'x')
	{
		if (Roatation == true)
			RocationOrder.push_front(MoveLeft);
		else if (Roatation == false)
			RocationOrder.push_back(MoveLeft);
	}
	else if (key == 'Y')
	{
		if (Roatation == true)
			RocationOrder.push_front(MoveUp);
		else if (Roatation == false)
			RocationOrder.push_back(MoveUp);
	}
	else if (key == 'y')
	{
		if (Roatation == true)
			RocationOrder.push_front(MoveDown);
		else if (Roatation == false)
			RocationOrder.push_back(MoveDown);

	}
	else if (key == 'R')
		RocationOrder.push_back(Spin);
	else if (key == 'r')
	{
		static int tempCnt;
		tempCnt++;
		RocationOrder.push_front(Spin);

		if (tempCnt % 8 == 0)
			Roatation = false;
		else
			Roatation = true;
	}
	else if (key == 'E')
		RocationOrder.push_back(Expand);
	else if (key == 'e')
		RocationOrder.push_front(Expand);
	else if (key == 'D')
		RocationOrder.push_back(DownScale);
	else if (key == 'd')
		RocationOrder.push_front(DownScale);


	else if (key == 'B')
		MoveROrder = true;

	else if (key == 'b')
		MoveROrder = false;

	else if (key == 'I' || key == 'i')
		Reset = true;

	else if (key == 'Q' || key == 'q')
		Quit = true;

}

GLvoid Mouse(int button, int state, int x, int y)
{


	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{
	if (MoveROrder == true)
	{
		if (ShapeOrder == DrawSin || ShapeOrder == DrawCos)
		{
			if (CurRDirection == 0)
				CurRDirection = -1;


			if (CurRDirection == -1 && CurR <= -45)
				CurRDirection = 1;
			if (CurRDirection == -1)
			{
				cout << CurR << endl;
				CurR -= 1;
			}

			if (CurRDirection == 1 && CurR >= 45)
				CurRDirection = -1;
			else if (CurRDirection == 1)
				CurR++;

		}
		
	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}

void ChangeDotsList()
{ 
		///���̺� ����Ʈ
	list<Point>::iterator itor = Dots.begin();
	if (ShapeOrder == DrawSin)									//drawSin
	{
		double angle = 0;

		CurCP.x = SceneInit_x + CurR;
		Point tempPoint;

		for (int i = 0; i < 1440; i++)
		{
			tempPoint.x = CurCP.x;
			tempPoint.y = CurR * sin(getRadian(angle));

			Dots.push_back(tempPoint);
			angle++;
			CurCP.x += 0.5;
		}
	}

	else if (ShapeOrder == DrawCos)								//drawCos
	{
		double angle = 0;

		CurCP.x = SceneInit_x + CurR;
		Point tempPoint;

		for (int i = 0; i < 1440; i++)
		{
			tempPoint.x = CurCP.x;
			tempPoint.y = CurR * cos(getRadian(angle));

			Dots.push_back(tempPoint);
			angle++;
			CurCP.x += 0.5;
		}
	}

	else if (ShapeOrder == DrawSpring)								//DrawSpring
	{

		double angle = 0;
		CurR = 90;
		CurCP.x = SceneInit_x;
		Point tempPoint;

		for (int i = 0; i < 1440; i++)
		{
			tempPoint.x = CurCP.x + CurR * cos(getRadian(angle));
			tempPoint.y = CurR * sin(getRadian(angle));

			Dots.push_back(tempPoint);
			angle++;

			CurCP.x += 0.5;
	
		}
	}

	else if (ShapeOrder == DrawRectangle)								//drawCos
	{
		Point tempPoint;

		tempPoint.x = -35;
		tempPoint.y = -35;

		Dots.push_back(tempPoint);

		tempPoint.x = 35;
		tempPoint.y = -35;

		Dots.push_back(tempPoint);

		tempPoint.x = 35;
		tempPoint.y = 35;

		Dots.push_back(tempPoint);

		tempPoint.x = -35;
		tempPoint.y = 35;

		Dots.push_back(tempPoint);

		tempPoint.x = -35;
		tempPoint.y = -35;

		Dots.push_back(tempPoint);

	}


}