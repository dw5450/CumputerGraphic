#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

#define RectNum 100
#define xLen 40	
#define yLen 40
#define Center_x 400
#define Center_y 300

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
struct Point
{
	double x;
	double y;
};

int RectCpCnt = 0;
Point RectCp[RectNum];
Point ClickPoint;

int RectColor = 1;
bool MotionRect = false;
int time1 = 0;


void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // 	�������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("�ǽ� 7"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �Լ��� ����
	glutMouseFunc(Mouse); // �ܼ� ���콺 �Է� �Լ��� ����
	glutTimerFunc(60, Timerfunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�


	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'blue' ���� ����

	for (int i = 0; i < RectNum; i++)
	{
		glRectf(RectCp[i].x - xLen / 2, RectCp[i].y - yLen / 2, RectCp[i].x + xLen / 2, RectCp[i].y + yLen / 2);
	}
	// ���� �����ϰ� �簢�� �׸��� ��
	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	
}

GLvoid Mouse(int button, int state, int x, int y)
{
	static int tempcnt = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		RectCp[tempcnt].x = x;
		RectCp[tempcnt].y = 600 - y;

		tempcnt++;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		ClickPoint.x = x;
		ClickPoint.y = 600 - y;
	}




	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{
	time1++;
	static int tempCnt = 0;

	if (ClickPoint.x > 0)
	{
		for (int i = 0; i < RectNum; i++)
		{
			if (RectCp[i].x > ClickPoint.x)
				RectCp[i].x -= 1;
			else if (RectCp[i].x < ClickPoint.x)
				RectCp[i].x += 1;
			if (RectCp[i].y > ClickPoint.y)
				RectCp[i].y -= 1;
			else if (RectCp[i].y < ClickPoint.y)
				RectCp[i].y += 1;
		}
	}

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(60, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}