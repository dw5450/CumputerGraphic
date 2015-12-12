#include<glut.h>
#include<iostream>
#include <list>
#include <cstdio>
#include "Player.h"
#include "Wall.h"

#define PI   3.14159265359


using namespace std;

//필요한 변수 선언

int ViewMode = 0;

Player Player1;

int map1[10][10] = { 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 1, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
					1, 0, 0, 1, 0, 0, 1, 0, 1, 0 };


Wall Walls1[100];
int WallNum = 0;

//글로벌 조명 설정용 변수
GLfloat GlobalAmbientLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };

//조명 0 설정용 변수
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat DiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0f };
GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos0[] = { 0.0, 0, 0, 1.0 };

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

	//플레이어 원 설정
	Player1.insertEye(Point3d(0.0, 0.0, 30.0));
	Player1.insertViewPoint(Point3d(0.0, 0.0, 29.0));


	//첫번째 맵 설정
	for (int i = 9; i >= 0; i--)
		for (int j = 0; j < 10; j++)
		{

			if (map1[i][j] == 1){
				Walls1[WallNum].insertPos(Point3d(j * 10, 0, (i - 9) * 10));
				Walls1[WallNum].insertSize(Point3d(10, 10, 10));

				WallNum++;
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
	gluLookAt(Eye.x, Eye.y, Eye.z, ViewPoint.x, ViewPoint.y, ViewPoint.z, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우
	
	//모델링 변환 : 모델 위치 설정
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // 설정된 색으로 전체를 칠하기, 깊이 설정


	//조명 효과 설정
	glEnable(GL_LIGHTING);                                    //조명 사용 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbientLight);         //전역 조명 모델 설정


	//물체 색 효과 속성 설정
	glEnable(GL_COLOR_MATERIAL);                              //컬러 트랙킹 설정(glColor3f사용 설정)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //재질 속성 설정(물체 색 효과 설정)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //하이라이트 색깔
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //하이라이트 계수
	glShadeModel(GL_SMOOTH);                                 //부드러운 쉐이딩

	//은면 제거, 컬링 설정
	glEnable(GL_DEPTH_TEST);                                 //은면 제거 
	//glEnable(GL_CULL_FACE);                                 //컬링
	//glFrontFace(GL_CCW);                                    //앞면 -> ccw(반시계 방향) 설정

	//조명 0 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);

	//조명0 on
	glEnable(GL_LIGHT0);

	glPushMatrix();



	//x축   빨간색
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(1, 0, 0);
	glEnd();

	//y축   초록색
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 1, 0);
	glEnd();


	//z축   //파란색
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 1);
	glEnd();


	//밑바닥  //파란색
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex3f(0, -5, 0);
		glVertex3f(0, -5, -200);
		glVertex3f(200, -5, -200);
		glVertex3f(200, -5, 0);
	glEnd();

	glPopMatrix();

	for (int i = 0; i < WallNum; i++)
	{
		Walls1[i].draw();
	}
		

	
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
	Player1.Move(key);
	Player1.ChangeViewPoint(key);
	
	bool wall_crush;
	for (int i = 0; i < WallNum; i++)
	{
		wall_crush = Player1.CrushWithWall(Walls1[i].returnHitBox());
		if (wall_crush)
			break;
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

