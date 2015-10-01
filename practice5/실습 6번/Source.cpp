#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

#define RectNum 10
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
double RectXlen[RectNum];
double RectYlen[RectNum];
double MaxLen[RectNum];
double Speed[RectNum];
int xDirection[RectNum];
int yDirection[RectNum];

int RectColor = 1;
bool MotionRect = false;
int time1 = 0;


void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // 	�������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("�ǽ� 6"); // ������ ���� (������ �̸�) 
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
	if (key == 'A')
		MotionRect = true;
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < RectNum; i++)
		{
			if (RectCp[i].x - xLen / 2 < x && x < RectCp[i].x + xLen / 2)
			{
				if (RectCp[i].y - yLen / 2 < 600 - y && 600 - y < RectCp[i].y + yLen / 2)
					MotionRect = true;
			}
		}
	}
	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{
	time1++;
	static int tempCnt = 0;

	if (time1 % 20 == 0 && tempCnt < RectNum)
	{
		RectCp[tempCnt].x = rand() % (800 - xLen * 2) + xLen;
		RectCp[tempCnt].y = rand() % (600 - yLen * 2) + yLen;

		int tempXLen;
		int tempYLen;
		tempXLen = abs(RectCp[tempCnt].x - Center_x);
		tempYLen = abs(RectCp[tempCnt].y - Center_y);

		if (tempXLen * 3 < tempYLen * 4)
		{
			if (RectCp[tempCnt].y > Center_y)
			{
				xDirection[tempCnt] = -1;
				yDirection[tempCnt] = 0;
			}
			else if (RectCp[tempCnt].y < Center_y)
			{
				xDirection[tempCnt] = 1;
				yDirection[tempCnt] = 0;
			}

			MaxLen[tempCnt] = tempYLen / 3 * 5;
		}

		else
		{
			if (RectCp[tempCnt].x < Center_x)
			{
				xDirection[tempCnt] = 0;
				yDirection[tempCnt] = -1;
			}
			else if (RectCp[tempCnt].x > Center_x)
			{
				xDirection[tempCnt] = 0;
				yDirection[tempCnt] = 1;
			}

			MaxLen[tempCnt] = tempXLen / 4 * 5;

		}


		Speed[tempCnt] = MaxLen[tempCnt] / 10;

		/*std::cout << RectCp[tempCnt].x << ", " << RectCp[tempCnt].y << std::endl<< MaxLen[tempCnt] << std::endl;
*/
		tempCnt++;
	}

	if (MotionRect == true)
	{
		for (int i = 0; i < tempCnt; i++)
		{

			int tempXLen;
			int tempYLen;
			tempXLen = abs(RectCp[i].x - Center_x);
			tempYLen = abs(RectCp[i].y - Center_y);
		
			if (sqrt(pow(tempXLen, 2) + pow(tempYLen, 2)) > MaxLen[i])
			
			{
				if (xDirection[i] > 0)
				{
					RectCp[i].x = Center_x + MaxLen[i] / 5 * 4;
					RectCp[i].y = Center_y - MaxLen[i] / 5 * 3;
					xDirection[i] = 0;
					yDirection[i] = 1;
				
				}
				
				else if (yDirection[i] > 0)
				{
					RectCp[i].x = Center_x + MaxLen[i] / 5 * 4;
					RectCp[i].y = Center_y + MaxLen[i] / 5 * 3;
					xDirection[i] = -1;
					yDirection[i] = 0;
				}

				else if (xDirection[i] < 0)
				{
					RectCp[i].x = Center_x - MaxLen[i] / 5 * 4;
					RectCp[i].y = Center_y + MaxLen[i] / 5 * 3;
					xDirection[i] = 0;
					yDirection[i] = -1;

				}

				else if (yDirection[i] < 0)
				{
					RectCp[i].x = Center_x - MaxLen[i] / 5 * 4;
					RectCp[i].y = Center_y - MaxLen[i] / 5 * 3;
					xDirection[i] = 1;
					yDirection[i] = -0;

				}


			}
			else
			{
				RectCp[i].x += Speed[i] * xDirection[i];
				RectCp[i].y += Speed[i] * yDirection[i];
			}
		}
	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(60, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}