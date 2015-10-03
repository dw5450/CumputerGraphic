

//도형 2개 그리고 변환 하기
//–화면의 중앙에 좌표계를 그린다. (원근 투영 적용)
//–화면에 도형을 좌우로 그린다.

//•메뉴또는 키보드 명령에 의해 도형을 선택하면, 좌측에는
//솔리드 모델이, 우측에는 와이어 모델이 그려진다.
//•선택 모델 : 구 / 육면체 / 원뿔 / 주전자
//–키보드를 이용하여 회전한다.
//•좌표계에 대한 회전
//–X : x축에 대하여 회전
// –Y : y축에 대하여 회전
//  –Z : z축에 대하여 회전
//	   –좌표계 전체가 회전하면서 두 개의 도형도 함께 회전한다.
//	   •도형 회전
//   –L : 왼쪽 도형이 제자리에서 임의의 회전축에 대하여 회전
//	–R : 오른쪽 도형이 제자리에서 임의의 회전축에 대하여 회전
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

#define SceneInit_x		-400.0
#define SceneInit_y		-300.0
#define SceneEnd_x		400.0
#define SceneEnd_y		300.0

using namespace std;

//필요한 변수 선언

int shape = 0;					//도형	1: 구 / 2: 육면체/ 3: 원뿔  / 4 : 주전자
char Rotation1;				//회전	X: x축 회전 / Y : y축 회전 / Z : z축 회전
double Xangle = 0;				//x축 각도
double Yangle = 0;				//y축 각도
double Zangle = 0;				//z축 각도

char Rotation2;				//회전  L: 왼쪽 회전/ R : 오른쪽 회전
double Leftangle = 0;			//왼쪽 도형 각도
double Rightangle = 0;			//오른쪽 도형 각도

///화면 컨트롤을 위한 기본 함수 선언
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
void ChangeDotsList();
double getRadian(double _num);

//각도 계산을 위한 라디안 함수

double getRadian(double _num)
{
	return _num * (PI / 180);
}
void main(int argc, char *argv[])
{
	//초기화 함수들 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 0); // 	윈도우의 위치지정 
	glutInitWindowSize(700, 700); // 윈도우의 크기 지정 
	glutCreateWindow("실습 13"); // 윈도우 생성 (윈도우 이름) 
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glPushMatrix();
		glTranslated(0.0, 0.0, -10.0);
		glRotated(Xangle, 1.0, 0.0, 0.0);
		glRotated(Yangle, 0.0, 1.0, 0.0);
		glRotated(Zangle, 0.0, 0.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장




	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	glColor3f(0.0, 1.0, 0.0);
	
	
	glPushMatrix();
		glTranslated(-2.5, 0.0, 0.0);
		glRotated(Leftangle, 0, 1, 0);

	if (shape == 1)
		glutWireSphere(1.1, 16, 16);
	else if (shape == 2)
		glutWireCube(1.1);
	else if (shape == 3)
	{
		glTranslated(0.0, -0.8, 0.0);
		glRotated(-90, 1, 0, 0);
		glutWireCone(0.7, 2.0, 16, 16);
	}
	else if (shape == 4)
		glutWireTeapot(1.1);
	
	glPopMatrix();



	glPushMatrix();
		glTranslated(2.5, 0.0, 0.0);
		glRotated(Rightangle, 0, 1, 0);

	if (shape == 1)
		glutSolidSphere(1.1, 16, 16);
	else if (shape == 2)
		glutSolidCube(1.1);
	else if (shape == 3)
	{
		glTranslated(0.0, -0.8, 0.0);
		glRotated(-90, 1, 0, 0);
		glutSolidCone(0.7, 2.0, 16, 16);
	}
	else if (shape == 4)
		glutSolidTeapot(1.1);

	glPopMatrix();


	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수

	//glOrtho(SceneInit_x, SceneEnd_x, SceneInit_y, SceneEnd_y, -1.0, 1.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
		shape = 1;
	else if (key == '2')
		shape = 2;
	else if (key == '3')
		shape = 3;
	else if (key == '4')
		shape = 4;


	else if (key == 'X' || key == 'x')
		Xangle+= 1.0;
	else if (key == 'Y' || key == 'y')
		Yangle+= 1.0;
	else if (key == 'Z' || key == 'z')
		Zangle += 1.0;


	else if (key == 'L' || key == 'l')
		Leftangle += 1.0;
	else if (key == 'R' || key == 'r')
		Rightangle += 1.0;


	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
}

GLvoid Mouse(int button, int state, int x, int y)
{

	


	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
}

void Timerfunction(int value)
{
	
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, Timerfunction, 1); // 타이머함수 재 설정
}

