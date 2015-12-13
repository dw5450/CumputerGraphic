#include<glut.h>
#include<iostream>
#include <list>
#include <cstdio>
#include "Player.h"
#include "Wall.h"
#include "MyFunction.h"
#include "EndPoint.h"
#include "Item.h"

#define PI   3.14159265359

#define PLAY		22222222
#define VIEW_MAP    22222221

#define TITLE 8321783
#define STAGE1 8321784
#define STAGE2 8321785
#define STAGE3 8321786
#define FINISH	83217




using namespace std;

//필요한 변수 선언

int ViewMode = 0;

int cur_state;

Player Player1;

//첫번째 맵 변수
int map1[10][10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
					3, 0, 0, 0, 0, 0, 0, 1, 1, 1,
					1, 1, 1, 0, 1, 1, 0, 0, 5, 1,
					1, 0, 0, 0, 0, 0, 1, 1, 1, 1,
					1, 5, 1, 5, 1, 0, 1, 0, 5, 1,
					1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
					1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
					1, 0, 1, 0, 1, 1, 0, 1, 0, 1,
					1, 5, 1, 0, 0, 0, 0, 1, 0, 2,
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };	//0 길 1 벽 2마지막 3처음 5아이템


int map2[15][15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
					1, 1, 1, 0, 0, 0, 1, 5, 1, 1, 5, 1, 1, 1, 1,
					1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 5, 1,
					1, 0, 0, 0, 1, 5, 1, 1, 0, 1, 1, 1, 0, 1, 1,
					1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
					1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1,
					1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
					1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1,
					3, 0, 1, 5, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1,
					1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
					1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
					1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 5, 1,
					1, 5, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
					1, 1, 1, 1, 1, 5, 1, 1, 1, 0, 1, 1, 1, 1, 1,
					1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, };


int map3[20][20] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
					1, 1, 1, 1, 1, 5, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 5, 1,
					1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1,
					1, 1, 0, 1, 1, 1, 1, 5, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
					1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 5, 1,
					1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1,
					1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 5, 1,
					1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
					1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
					1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1,
					1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
					1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 5, 0, 1, 1, 0, 1, 0, 0, 0, 1,
					1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1,
					1, 5, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
					1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
					1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1,
					1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 5, 1, 1, 0, 1, 1, 1, 0, 1,
					1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 5, 0, 1,
					1, 0, 1, 0, 0, 0, 1, 5, 1, 1, 1, 1, 1, 5, 0, 5, 1, 1, 1, 1,
					1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };


Wall Walls1[100];
int Wall1Num = 0;
EndPoint EndPoint1;
Item Item1[100];
int Item1Num = 0;

Wall Walls2[225];
int Wall2Num = 0;
EndPoint EndPoint2;
Item Item2[100];
int Item2Num = 0;


Wall Walls3[400];
int Wall3Num = 0;
EndPoint EndPoint3;
Item Item3[100];
int Item3Num = 0;

int CCV_NUM = 0;



//글로벌 조명 설정용 변수
GLfloat GlobalAmbientLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };


//조명 0 설정용 변수
GLfloat AmbientLight1[] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat DiffuseLight1[] = { 0.7, 0.7, 0.7, 1.0f };
GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos1[] = { 50, 10, -50, 1.0 };


//컬러 설정용 변수
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLvoid drawScene(GLvoid);
void drawTitle();
void drawStage1();
void drawStage2();
void drawStage3();
void drawFinish();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
double getRadian(double _num);

void load_statge1()
{

	//첫번째 맵 설정
	for (int i = 9; i >= 0; i--)
		for (int j = 0; j < 10; j++)
		{
			if (map1[i][j] == 1){
				Walls1[Wall1Num].insertPos(Point3d(j * 10 + 5, 0, (i - 9) * 10 - 5));
				Walls1[Wall1Num].insertSize(Point3d(10, 10, 10));

				Wall1Num++;
			}

			if (map1[i][j] == 2){
				EndPoint1.insertPos(Point3d(j * 10 + 5, 0, (i - 9) * 10 - 5));
				EndPoint1.insertSize(Point3d(10, 10, 10));

			}

			if (map1[i][j] == 5){
				Item1[Item1Num].insertPos(Point3d(j * 10 + 5, 0, (i - 9) * 10 - 5));
				Item1[Item1Num].insertSize(Point3d(10, 10, 10));
				Item1Num++;

			}
		}

	cur_state = STAGE1;
	//뷰 모드 설정

	ViewMode = PLAY;
	//플레이어 원 설정
	Player1.insertEye(Point3d(5.0, 0.0, -85.0));
	Player1.insertViewPoint(Point3d(6.0, 0.0, -85.0));
	Player1.insertViewMode(VIEWRIGHT);


	LightPos1[0] = 50;
	LightPos1[1] = 30;
	LightPos1[2] = -50;
	LightPos1[3] = 1;
}

void load_statge2()
{
	//두번째 맵 설정
	for (int i = 14; i >= 0; i--)
		for (int j = 0; j < 15; j++)
		{
			if (map2[i][j] == 1){
				Walls2[Wall2Num].insertPos(Point3d(j * 10 + 5, 0, (i - 14) * 10 - 5));
				Walls2[Wall2Num].insertSize(Point3d(10, 10, 10));

				Wall2Num++;
			}

			if (map2[i][j] == 2){
				EndPoint2.insertPos(Point3d(j * 10 + 5, 0, (i - 14) * 10 - 5));
				EndPoint2.insertSize(Point3d(10, 10, 10));
			}

			if (map2[i][j] == 5){
				Item2[Item2Num].insertPos(Point3d(j * 10 + 5, 0, (i - 14) * 10 - 5));
				Item2[Item2Num].insertSize(Point3d(10, 10, 10));
				Item2Num++;

			}
		}

	cur_state = STAGE2;
	//뷰 모드 설정

	ViewMode = PLAY;
	//플레이어 원 설정
	Player1.insertEye(Point3d(5.0, 0.0, -65.0));
	Player1.insertViewPoint(Point3d(6.0, 0.0, -65.0));
	Player1.insertViewMode(VIEWRIGHT);


	LightPos1[0] = 75;
	LightPos1[1] = 30;
	LightPos1[2] = -75;
	LightPos1[3] = 1;
}

void load_statge3()
{
	//세번째 맵 설정
	for (int i = 19; i >= 0; i--)
		for (int j = 0; j < 20; j++)
		{
			if (map3[i][j] == 1){
				Walls3[Wall3Num].insertPos(Point3d(j * 10 + 5, 0, (i - 19) * 10 - 5));
				Walls3[Wall3Num].insertSize(Point3d(10, 10, 10));

				Wall3Num++;
			}

			if (map3[i][j] == 2){
				EndPoint3.insertPos(Point3d(j * 10 + 5, 0, (i - 19) * 10 - 5));
				EndPoint3.insertSize(Point3d(10, 10, 10));
			}

			if (map1[i][j] == 5){
				Item3[Item3Num].insertPos(Point3d(j * 10 + 5, 0, (i - 19) * 10 - 5));
				Item3[Item3Num].insertSize(Point3d(10, 10, 10));
				Item3Num++;

			}
		}


	cur_state = STAGE3;
	//뷰 모드 설정

	ViewMode = PLAY;
	//플레이어 원 설정
	Player1.insertEye(Point3d(95.0, 0.0, -195.0));
	Player1.insertViewPoint(Point3d(95.0, 0.0, -194.0));
	Player1.insertViewMode(VIEWBACK);


	LightPos1[0] = 100;
	LightPos1[1] = 30;
	LightPos1[2] = -100;
	LightPos1[3] = 1;

}

void initialize()
{

	load_statge3();
}


void main(int argc, char *argv[])
{
	//초기화 함수들 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 0); //    윈도우의 위치지정 
	glutInitWindowSize(700, 700); // 윈도우의 크기 지정 
	glutCreateWindow("컴퓨터 그래픽 기본 코드 by 2014180026"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 함수의 지정
	glutMouseFunc(Mouse); // 단순 마우스 입력 함수의 지정
	glutTimerFunc(100, Timerfunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 

	initialize();

	glutMainLoop();

}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	if (cur_state == TITLE)
	{

	}
	if (cur_state == STAGE1) drawStage1();
		
	if (cur_state == STAGE2) drawStage2();

	if (cur_state == STAGE3) drawStage3();

	if (cur_state == FINISH)
	{	
		
	}


	glPopMatrix();

	//조명 0 설정
	
	glutSwapBuffers();
}


void drawStage1()
{
	//관측 변환 : 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);               // 직각 투영을 사용하는 경우
	gluPerspective(60.0, 1.0, 1.0, 1000.0);                     // 원근 투영을 사용하는 경우

	Point3d Eye = Player1.returnEye();
	Point3d ViewPoint = Player1.returnViewPoint();

	if (ViewMode == PLAY)
		gluLookAt(Eye.x, Eye.y + 0.1, Eye.z, ViewPoint.x, ViewPoint.y, ViewPoint.z, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우

	else if (ViewMode == VIEW_MAP){

		gluLookAt(50, 200.0, -50, 51, -1, -50, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우
		glPushMatrix();

	}

	//모델링 변환 : 모델 위치 설정
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // 설정된 색으로 전체를 칠하기, 깊이 설정


	//조명 효과 설정
	glEnable(GL_LIGHTING);                                    //조명 사용 설정


	//물체 색 효과 속성 설정
	glEnable(GL_COLOR_MATERIAL);                              //컬러 트랙킹 설정(glColor3f사용 설정)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //재질 속성 설정(물체 색 효과 설정)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //하이라이트 색깔
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //하이라이트 계수
	glShadeModel(GL_SMOOTH);                                 //부드러운 쉐이딩

	//은면 제거, 컬링 설정
	glEnable(GL_DEPTH_TEST);                                 //은면 제거 
	glEnable(GL_CULL_FACE);                                 //컬링
	glFrontFace(GL_CCW);                                    //앞면 -> ccw(반시계 방향) 설정
	//밑바닥  //파란색


	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);

	//조명0 on
	glEnable(GL_LIGHT1);

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(50, -5, -50);
	glScaled(1, 0.001, 1);
	drawCube(100);

	glPopMatrix();

	glColor3f(1, 0, 0);
	Player1.draw();
	glColor3f(0, 0, 1);
	for (int i = 0; i < Wall1Num; i++)
	{
		Walls1[i].draw();
	}

	for (int i = 0; i < Item1Num; i++)
	{
		Item1[i].draw();
	}


	EndPoint1.draw();
	
}

void drawStage2()
{
	//관측 변환 : 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);               // 직각 투영을 사용하는 경우
	gluPerspective(60.0, 1.0, 1.0, 1000.0);                     // 원근 투영을 사용하는 경우

	Point3d Eye = Player1.returnEye();
	Point3d ViewPoint = Player1.returnViewPoint();

	if (ViewMode == PLAY)
		gluLookAt(Eye.x, Eye.y + 0.1, Eye.z, ViewPoint.x, ViewPoint.y, ViewPoint.z, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우

	else if (ViewMode == VIEW_MAP){

		gluLookAt(75, 200.0, -75, 75, -1, -74, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우
		glPushMatrix();

	}

	//모델링 변환 : 모델 위치 설정
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // 설정된 색으로 전체를 칠하기, 깊이 설정


	//조명 효과 설정
	glEnable(GL_LIGHTING);                                    //조명 사용 설정


	//물체 색 효과 속성 설정
	glEnable(GL_COLOR_MATERIAL);                              //컬러 트랙킹 설정(glColor3f사용 설정)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //재질 속성 설정(물체 색 효과 설정)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //하이라이트 색깔
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //하이라이트 계수
	glShadeModel(GL_SMOOTH);                                 //부드러운 쉐이딩

	//은면 제거, 컬링 설정
	glEnable(GL_DEPTH_TEST);                                 //은면 제거 
	glEnable(GL_CULL_FACE);                                 //컬링
	glFrontFace(GL_CCW);                                    //앞면 -> ccw(반시계 방향) 설정
	//밑바닥  //파란색


	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);

	//조명0 on
	glEnable(GL_LIGHT1);

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(50, -5, -50);
	glScaled(1, 0.001, 1);
	drawCube(100);

	glPopMatrix();


		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslated(75, -5, -75);
		glScaled(1, 0.001, 1);
		drawCube(150);

	glPopMatrix();

	glColor3f(0, 0, 1);
	for (int i = 0; i < Wall2Num; i++)
	{
		
		Walls2[i].draw();
	}

	for (int i = 0; i < Item2Num; i++)
	{
		Item2[i].draw();
	}

	EndPoint2.draw();

	Player1.draw();
}

void drawStage3()
{
	//관측 변환 : 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);               // 직각 투영을 사용하는 경우
	gluPerspective(60.0, 1.0, 1.0, 1000.0);                     // 원근 투영을 사용하는 경우

	Point3d Eye = Player1.returnEye();
	Point3d ViewPoint = Player1.returnViewPoint();

	if (ViewMode == PLAY)
		gluLookAt(Eye.x, Eye.y + 0.1, Eye.z, ViewPoint.x, ViewPoint.y, ViewPoint.z, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우

	else if (ViewMode == VIEW_MAP){

		gluLookAt(100, 300.0, -100, 101, -1, -100, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우
		glPushMatrix();

	}

	//모델링 변환 : 모델 위치 설정
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // 설정된 색으로 전체를 칠하기, 깊이 설정


	//조명 효과 설정
	glEnable(GL_LIGHTING);                                    //조명 사용 설정


	//물체 색 효과 속성 설정
	glEnable(GL_COLOR_MATERIAL);                              //컬러 트랙킹 설정(glColor3f사용 설정)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //재질 속성 설정(물체 색 효과 설정)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //하이라이트 색깔
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //하이라이트 계수
	glShadeModel(GL_SMOOTH);                                 //부드러운 쉐이딩

	//은면 제거, 컬링 설정
	glEnable(GL_DEPTH_TEST);                                 //은면 제거 
	glEnable(GL_CULL_FACE);                                 //컬링
	glFrontFace(GL_CCW);                                    //앞면 -> ccw(반시계 방향) 설정
	//밑바닥  //파란색


	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);

	//조명0 on
	glEnable(GL_LIGHT1);

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(50, -5, -50);
	glScaled(1, 0.001, 1);
	drawCube(100);

	glPopMatrix();


	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(100, -5, -100);
	glScaled(1, 0.001, 1);
	drawCube(200);

	glPopMatrix();

	glColor3f(0, 0, 1);
	for (int i = 0; i < Wall3Num; i++)
	{
		Walls3[i].draw();
	}

	for (int i = 0; i < Item3Num; i++)
	{
		Item3[i].draw();
	}

	EndPoint3.draw();

	Player1.draw();

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

	if (ViewMode == PLAY){
		Player1.Move(key);
		Player1.ChangeViewPoint(key);
	}

	if (cur_state == STAGE1)
	{
		bool wall_crush;
		for (int i = 0; i < Wall1Num; i++)
		{
			wall_crush = Player1.CrushWithWall(Walls1[i].returnHitBox());
			if (wall_crush)
				break;
		}

		bool item_crush;
		for (int i = 0; i < Item1Num; i++)
		{
			item_crush = Player1.CrushWithItem(Item1[i].returnHitBox());
			if (item_crush){
				CCV_NUM++;
				Item1[i].insertPos(Point3d(-1000, -1000, 1000));
				break;
			}
		}
		if (Player1.CrushWithEndPoint(EndPoint1.returnHitBox())) load_statge2();
	}


	if (cur_state == STAGE2)
	{
		bool wall_crush;
		for (int i = 0; i < Wall2Num; i++)
		{
			wall_crush = Player1.CrushWithWall(Walls2[i].returnHitBox());
			if (wall_crush)
				break;
		}

		bool item_crush;
		for (int i = 0; i < Item2Num; i++)
		{
			item_crush = Player1.CrushWithItem(Item2[i].returnHitBox());
			if (item_crush){
				CCV_NUM++;
				Item2[i].insertPos(Point3d(-1000, -1000, 1000));
				break;
			}
		}

		if (Player1.CrushWithEndPoint(EndPoint1.returnHitBox())) load_statge3();

	}


	if (cur_state == STAGE3)
	{
		bool wall_crush;
		for (int i = 0; i < Wall3Num; i++)
		{
			wall_crush = Player1.CrushWithWall(Walls3[i].returnHitBox());
			if (wall_crush)
				break;
		}

		bool item_crush;
		for (int i = 0; i < Item3Num; i++)
		{
			item_crush = Player1.CrushWithItem(Item3[i].returnHitBox());
			if (item_crush){
				CCV_NUM++;
				Item3[i].insertPos(Point3d(-1000, -1000, 1000));
				break;
			}
		}
	}

	if (key == 'q')
	{
		if (ViewMode == PLAY && CCV_NUM > 0)	{
			ViewMode = VIEW_MAP;
			CCV_NUM--;
		}
		else if (ViewMode == VIEW_MAP)	ViewMode = PLAY;
	}

	if (key == 'i')
		initialize();


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

