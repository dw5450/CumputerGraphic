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
	//초기화 함수들 

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 	윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("실습 8"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 함수의 지정
	glutMouseFunc(Mouse); // 단순 마우스 입력 함수의 지정
	glutTimerFunc(60, Timerfunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기


	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // 그리기 색을 'blue' 으로 지정

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
	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
}

void Timerfunction(int value)
{
	time1++;
	static int tempCnt = 0;

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(60, Timerfunction, 1); // 타이머함수 재 설정
}

double getRadian(double _num)
{
	return _num * (PI / 180);
}