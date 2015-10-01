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
	//초기화 함수들 

	for (int i = 0; i < 10; i++)
	{
		xDirection[i] = 10;
		yDirection[i] = 10;
	}


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 	윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("실습 1"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 함수의 지정
	glutMouseFunc(Mouse); // 단순 마우스 입력 함수의 지정
	glutTimerFunc(100, Timerfunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	if (RectColor == 1)
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // 그리기 색을 'blue' 으로 지정
	else if (RectColor == 2)
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // 그리기 색을 'blue' 으로 지정

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
	// 색상 지정하고 사각형 그리기 …
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == 'A' || key == 'a')					//색상 변경
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
	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
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
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, Timerfunction, 1); // 타이머함수 재 설정
}