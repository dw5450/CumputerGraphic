#include<glut.h>
#include<iostream>
#include <list>
#include <cstdio>
#include "Player.h"
#include "Wall.h"
#include "MyFunction.h"

#define PI   3.14159265359

#define PLAY		22222222
#define VIEW_MAP    22222221

#define TITLE 8321783
#define STAGE1 8321783
#define STAGE2 8321784
#define STAGE3 8321785
#define END	8321786




using namespace std;

//필요한 변수 선언

int ViewMode = 0;

int cur_state;

Player Player1;

int map1[10][10] = { 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 1, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					0, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					0, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					0, 0, 0, 1, 0, 0, 1, 0, 1, 0 };


Wall Walls1[100];
int Wall1Num = 0;

//글로벌 조명 설정용 변수
GLfloat GlobalAmbientLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };

//조명 0 설정용 변수
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat DiffuseLight0[] = { 0.7, 0.7, 0.7, 1.0f };
GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos0[] = { 0, 0, 0, 1.0 };

//조명 0 설정용 변수
GLfloat AmbientLight1[] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat DiffuseLight1[] = { 0.7, 0.7, 0.7, 1.0f };
GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos1[] = { 50, 10, -50, 1.0 };


//컬러 설정용 변수
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
double getRadian(double _num);

void initialize()

{

	cur_state = STAGE1;
	//뷰 모드 설정

	ViewMode = PLAY;
	//플레이어 원 설정
	Player1.insertEye(Point3d(0.0, 0.0, 30.0));
	Player1.insertViewPoint(Point3d(0.0, 0.0, 29.0));


	//첫번째 맵 설정
	for (int i = 9; i >= 0; i--)
		for (int j = 0; j < 10; j++)
		{
			if (map1[i][j] == 1){
				Walls1[Wall1Num].insertPos(Point3d(j * 10, 0, (i - 9) * 10));
				Walls1[Wall1Num].insertSize(Point3d(10, 10, 10));

				Wall1Num++;
			}
		}
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

		gluLookAt(50, 100.0, -50, 49, -1, -50, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우
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
	glShadeModel(GL_FLAT);                                 //부드러운 쉐이딩

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


	glColor3f(0, 0, 1);
	for (int i = 0; i < Wall1Num; i++)
	{
		Walls1[i].draw();
	}


	glColor3f(1, 0, 0);
	glPushMatrix();
		glTranslated(LightPos0[0], LightPos0[1], LightPos0[2]);
		glutSolidCube(1);

	glPopMatrix();

	//조명 0 설정
	
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
	Player1.Move(key);
	Player1.ChangeViewPoint(key);
	
	bool wall_crush;
	for (int i = 0; i < Wall1Num; i++)
	{
		wall_crush = Player1.CrushWithWall(Walls1[i].returnHitBox());
		if (wall_crush)
			break;
	}

	cout << Player1.returnViewPoint().x << endl;
	cout << Player1.returnViewPoint().z << endl;

	if (key == 'q')
	{
		if (ViewMode == PLAY)	ViewMode = VIEW_MAP;
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

