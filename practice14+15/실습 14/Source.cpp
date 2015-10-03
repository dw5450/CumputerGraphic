



//중심의 구를 중심으로 3개의 구가 다른 방향의 경로를 따라 회전하는 애니메이션 제작, 각 구에는 그 구를 중심으로 달이 공전한다.
//–경로 1: xz 평면
//–경로 2 : xz 평면이 반시계방향으로 45도 기울어져 있다.
//–경로 3 : xz 평면이 시계방향으로 45도 기울어져 있다.
//–3개의 구는 다른 속도로 중심의 구를 공전한다.
//–3개의 구에는 각각 공전하는 달을 가지고 있다.
//–메뉴를 이용하여 구의 모델을 선택할 수 있게 한다.
//•솔리드 모델 / 와이어 모델
//–원근 투영을 적용한다.
//–키보드 명령어에 의해서 경로 2( q, e)와 3 (a, s)의 기울임 각도를 움직일 수 있도록 한다.
//X/x : x축	기준으로 양/음의 방향으로 회전
//y/Y : y축 기준으로 양/음의 방향으로 회전
//z/Z : z축 기준으로 양/음의 방향으로 회전
//p/o : x축 방향으로 양/음의 방향으로 이동
//l/k : x축 방향으로 양/음의 방향으로 이동
//m/n : x축 방향으로 양/음의 방향으로 이동
//i : 초기화


#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<Windows.h>
#include<list>
#include<algorithm>

#define PI   3.14159265359

using namespace std;

//필요한 변수 선언

GLdouble Angle;
GLint Shape;
GLdouble TrackOneAngle = 45;
GLdouble TrackTwoAngle = -45;

double Xangle = 0;				//x축 각도
double Yangle = 0;				//y축 각도
double Zangle = 0;				//z축 각도

double ViewingX = 0;
double ViewingY = 0;
double ViewingZ = 0;

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

void rotatedraw(double r){
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 120; ++i){
			glVertex2f(r * cos(3 * i * (PI / 180)), r * sin(3 * i * (PI / 180)));
	}
	glEnd();
}

void main(int argc, char *argv[])
{
	//초기화 함수들 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 0); //    윈도우의 위치지정 
	glutInitWindowSize(700, 700); // 윈도우의 크기 지정 
	glutCreateWindow("실습 14"); // 윈도우 생성 (윈도우 이름) 
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

	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslated(ViewingX, ViewingY, -10.0 + ViewingZ);
	glRotated(Xangle, 1.0, 0.0, 0.0);
	glRotated(Yangle, 0.0, 1.0, 0.0);
	glRotated(Zangle, 0.0, 0.0, 1.0);



	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	
	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);

	//중앙 원
	if (Shape == 1)
		glutSolidSphere(0.5, 16, 16);
	else if (Shape == 2)
		glutWireSphere(0.5, 16, 16);
	//track 0
	glPushMatrix();
	glRotated(90 + Angle * 1.1, 0, 1, 0);


	//궤도 적용
		glRotated(90, 1, 0, 0);
		rotatedraw(3.0);
		glRotated(90, -1, 0, 0);

	glTranslated(-3.0, 0, 0);

	if (Shape == 1)
		glutSolidSphere(0.3, 16, 16);
	else if (Shape == 2)
		glutWireSphere(0.3, 16, 16);
	

		glPushMatrix();
			glRotated(-90 - Angle * 1.1, 0, 1, 0);
			glRotated(Angle * 3, 0, 1, 0);

			//궤도 적용
				glRotated(90, 1, 0, 0);
				rotatedraw(1.0);
				glRotated(90, -1, 0, 0);

			glTranslated(-1.0, 0, 0);

		if (Shape == 1)
			glutSolidSphere(0.1, 16, 16);
		else if (Shape == 2)
			glutWireSphere(0.1, 16, 16);

		glPopMatrix();

	glPopMatrix();

	//track 1
	glPushMatrix();
		glRotated(TrackOneAngle, 0, 0, 1);
		glRotated(Angle, 0, 1, 0);

		//궤도 적용
			glRotated(90, 1, 0, 0);
			rotatedraw(3.0);
			glRotated(90, -1, 0, 0);

		glTranslated(-3.0, 0, 0);

		if (Shape == 1)
			glutSolidSphere(0.3, 16, 16);
		else if (Shape == 2)
			glutWireSphere(0.3, 16, 16);

		glPushMatrix();

		glRotated(-Angle, 0, 1, 0);
		glRotated(-TrackOneAngle, 0, 0, 1);
		glRotated(Angle * 3, 0, 1, 0);

		//궤도 적용
			glRotated(90, 1, 0, 0);
			rotatedraw(1.0);
			glRotated(90, -11, 0, 0);

		glTranslated(-1.0, 0, 0);

		if (Shape == 1)
			glutSolidSphere(0.1, 16, 16);
		else if (Shape == 2)
			glutWireSphere(0.1, 16, 16);

		glPopMatrix();

	glPopMatrix();

	//track2
	glPushMatrix();
		glRotated(TrackTwoAngle * 0.8, 0, 0, 1);
		glRotated(180 + Angle * 0.8, 0, 1, 0);

		//궤도 적용
			glRotated(90, 1, 0, 0);
			rotatedraw(3.0);
			glRotated(90, -1, 0, 0);

		glTranslated(-3.0, 0, 0);

		if (Shape == 1)
			glutSolidSphere(0.3, 16, 16);
		else if (Shape == 2)
			glutWireSphere(0.3, 16, 16);

		glPushMatrix();

		glRotated(-180 - Angle * 0.8, 0, 1, 0);
		glRotated(-TrackTwoAngle, 0, 0, 1);
		glRotated(Angle * 3, 0, 1, 0);
		//궤도 적용
			glRotated(90, 1, 0, 0);
			rotatedraw(1.0);
			glRotated(90, -1, 0, 0);

		glTranslated(-1.0, 0, 0);

		if (Shape == 1)
			glutSolidSphere(0.1, 16, 16);
		else if (Shape == 2)
			glutWireSphere(0.1, 16, 16);

		glPopMatrix();


	glPopMatrix();

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
		Shape = 1;
	else if (key == '2')
		Shape = 2;

	else if (key == 'o')
		ViewingX += 1.0;
	else if (key == 'p')
		ViewingX -= 1.0;
	else if (key == 'k')
		ViewingY += 1.0;
	else if (key == 'l')
		ViewingY -= 1.0;
	else if (key == 'n')
		ViewingZ += 1.0;
	else if (key == 'm')
		ViewingZ -= 1.0;

	else if (key == 'q')
		TrackOneAngle -= 1.0;
	else if (key == 'w')
		TrackOneAngle += 1.0;
	else if (key == 'a')
		TrackTwoAngle -= 1.0;
	else if (key == 's')
		TrackTwoAngle += 1.0;

	else if (key == 'X')
		Xangle += 1.0;
	else if (key == 'x')
		Xangle -= 1.0;
	else if (key == 'Y')
		Yangle += 1.0;
	else if (key == 'y')
		Yangle -= 1.0;
	else if (key == 'Z')
		Zangle += 1.0;
	else if (key == 'z')
		Zangle -= 1.0;

	else if (key == 'i')
	{
	 Xangle = 0;				//x축 각도
	 Yangle = 0;				//y축 각도
	 Zangle = 0;				//z축 각도

	 ViewingX = 0;
		 ViewingY = 0;
	 ViewingZ = 0;
	}

	cout << "(" << ViewingX << ", " << ViewingY << ", " << ViewingZ << ")" << endl;

	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
}

GLvoid Mouse(int button, int state, int x, int y)
{




	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
}

void Timerfunction(int value)
{

	Angle += 3.0;

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, Timerfunction, 1); // 타이머함수 재 설정
}
