#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

#define ClickNum 10
#define xLen 4	
#define yLen 4
#define Center_x 400
#define Center_y 300
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
double getRadian(double _num);

struct Point

{
	double x;
	double y;
};

int RectCpCnt = 0;
Point ClickPoint[ClickNum];
int clickCnt = 0;
int R[10];

int time1 = 0;


void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // 	�������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("�ǽ� 8"); // ������ ���� (������ �̸�) 
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

	double tempNum;
	for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < 16; j++)
		{
			if (R[i] < 800)
			{
				tempNum = getRadian(360 / 16 * j);
				glRectf(R[i] * cos(tempNum) + ClickPoint[i].x - xLen / 2, R[i] * sin(tempNum) + ClickPoint[i].y - yLen / 2,
					R[i] * cos(tempNum) + ClickPoint[i].x + xLen / 2, R[i] * sin(tempNum) + ClickPoint[i].y + yLen / 2);
			}
			if (ClickPoint[i].x > 0)
				R[i] ++;
		}
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
		ClickPoint[tempcnt].x = x;
		ClickPoint[tempcnt].y = 600 - y;
		R[tempcnt] = 0;
		tempcnt++;
		

		if (tempcnt > 9)
		{
			tempcnt = 0;
		}
	}
	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{
	time1++;
	static int tempCnt = 0;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(60, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}

double getRadian(double _num)
{
	return _num * (PI / 180);
}