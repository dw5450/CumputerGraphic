#include<glut.h>
#include<iostream>

#define RectNum 10

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
struct Point
{
	int x;
	int y;
};

int RectCpCnt = 0;
Point RectCp[RectNum];
int RectColor = 1;
bool MotionRect = false;
int time = 0;
int xDirection[10];
int yDirection[10];

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	for (int i = 0; i < 10; i++)
	{
		xDirection[i] = 10;
		yDirection[i] = 10;
	}


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // 	�������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("�ǽ� 1"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �Լ��� ����
	glutMouseFunc(Mouse); // �ܼ� ���콺 �Է� �Լ��� ����
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	if (RectColor == 1)
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'blue' ���� ����
	else if (RectColor == 2)
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // �׸��� ���� 'blue' ���� ����

	for (int i = 0; i < RectNum; i++)
	{
		if (MotionRect == true)
		{
			if (time % 2 == 1)
				glRectf(RectCp[i].x - 20, RectCp[i].y - 10, RectCp[i].x + 20, RectCp[i].y + 10);
			else if (time % 2 == 0)
				glRectf(RectCp[i].x - 10, RectCp[i].y - 20, RectCp[i].x + 10, RectCp[i].y + 20);
		}
		else
			glRectf(RectCp[i].x - 20, RectCp[i].y - 10, RectCp[i].x + 20, RectCp[i].y + 10);
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
	if (key == 'A' || key == 'a')					//���� ����
	{
		RectColor++;
		
		if (RectColor > 2)
			RectColor = 1;
	}
	else if (key == 'B' || key == 'b')
	{
		if (MotionRect == true)
			MotionRect = false;
		else if (MotionRect == false)
			MotionRect = true;
	}

	else if (key == 'C' || key == 'c')
	{
		for (int i = 0; i < 10; i++)
		{
			if (xDirection[i] >= 0)
				xDirection[i] += 10;
			else if (xDirection[i] <= 0)
				xDirection[i] -= 10;
		}
	}

	else if (key == 'D' || key == 'd')
	{
		for (int i = 0; i < 10; i++)
		{
			if (xDirection[i] >= 0)
				xDirection[i] -= 10;
			else if (xDirection[i] <= 0)
				xDirection[i] += 10;
		}
	}

	else if (key == 'E' || key == 'e')
	{
		for (int i = 0; i < 10; i++)
		{
			if (yDirection[i] >= 0)
				yDirection[i] += 10;
			else if (yDirection[i] <= 0)
				yDirection[i] -= 10;
		}
	}

	else if (key == 'F' || key == 'f')
	{
		for (int i = 0; i < 10; i++)
		{
			if (yDirection[i] >= 0)
				yDirection[i] -= 10;
			else if (yDirection[i] <= 0)
				yDirection[i] += 10;
		}
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		RectCp[RectCpCnt].x = x;
		RectCp[RectCpCnt].y = 600 - y;

		RectCpCnt++;

		if (RectCpCnt > 9)
			RectCpCnt = 0;
	}
	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{
	time++;

	for (int i = 0; i < RectNum; i++)
	{
		RectCp[i].x += xDirection[i];
		RectCp[i].y += yDirection[i];

		if (RectCp[i].x > 800 && xDirection[i] > 0)
			xDirection[i] = -xDirection[i];
		else if (RectCp[i].x < 0 && xDirection[i] <0)
			xDirection[i] = -xDirection[i];

		if (RectCp[i].y > 600 && yDirection[i] > 0)
			yDirection[i] = -yDirection[i];
		else if (RectCp[i].y < 0 && yDirection[i] < 0)
			yDirection[i] = -yDirection[i];;
	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}