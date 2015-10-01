


//1. 삼각형이 가로로 직선 이동 앞뒤로 왔다갔다



//2. 삼각형이 달팽이 껍질 무늬처럼 이동 앞뒤로 왔다갔다



//3. 삼각형이 지그재그 이동 앞뒤로 왔다 갔다.



//4. 삼각형이 이동하는 위치를 찍으면 그 위치에 따라 앞뒤로 왔다갔다.




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

#define Translate		215123
#define Rotate			215124
#define Scale			215125

#define triangle		216123
#define rectangle		216124

using namespace std;

//필요한 변수 선언

struct ModleChange

{
	int type = NULL;
	double angle = NULL;
	double x = NULL;
	double y = NULL;
	double z = NULL;

	ModleChange(){}
	ModleChange(int Type, double Angle, double X, double Y, double Z)
		: type(Type), angle(Angle), x(X), y(Y), z(Z){}

	void InPut(int Type, double Angle, double X, double Y, double Z)
	{
		type = Type;
		angle = Angle;
		x = X;
		y = Y;
		z = Z;
	}

};

struct Point

{
	double x;
	double y;
};

bool Reset = false;
bool Quit = false;

int shape = triangle;
int MoveType = 0;
bool Move4Buffer;
bool MoveInit;

Point Path[5];
int PathCnt = 0;



list<ModleChange> ModleChangeList;
ModleChange TempModleChange;

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 	윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("실습 12"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 함수의 지정
	glutMouseFunc(Mouse); // 단순 마우스 입력 함수의 지정
	glutTimerFunc(100, Timerfunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	if (!Quit)
		glutMainLoop();

}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	list<ModleChange>::iterator itor = ModleChangeList.begin();


	//행렬 초기화
	for (itor = ModleChangeList.begin(); itor != ModleChangeList.end(); itor++)
	{
		glPopMatrix();
	}

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);				// 그리기 색을 'blue' 으로 지정

	//GL_LINE이 안그려져서 편법 쓴 부분, 구분선
	glBegin(GL_LINE_STRIP);
	{
		glVertex2i(0, SceneInit_x);
		glVertex2i(0, SceneEnd_y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	{
		glVertex2i(SceneInit_x, 0);
		glVertex2i(SceneEnd_x, 0);
	}
	glEnd();

	//행렬 변환 적용 부분
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for (itor = ModleChangeList.begin(); itor != ModleChangeList.end(); itor++)
	{
		if (itor->type == Translate)
			glTranslated(itor->x, itor->y, itor->z);

		else if (itor->type == Rotate)
			glRotated(itor->angle, itor->x, itor->y, itor->z);

		else if (itor->type == Scale)
			glScaled(itor->x, itor->y, itor->z);
	}


	//도형을 그리는 부분
	if (shape == triangle)
	{
		glBegin(GL_POLYGON);

		glVertex2i(0, 20);
		glVertex2i(-15, -10);
		glVertex2i(15, -10);

		glEnd();
	}


	else if (shape == rectangle)
	{
		glBegin(GL_POLYGON);

		glVertex2i(15, 15);
		glVertex2i(-15, 15);
		glVertex2i(-15, -15);
		glVertex2i(15, -15);

		glEnd();
	}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(SceneInit_x, SceneEnd_x, SceneInit_y, SceneEnd_y, -1.0, 1.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	MoveInit = 1;

	if (key == '1')
		MoveType = 1;
	else if (key == '2')
		MoveType = 2;
	else if (key == '3')
		MoveType = 3;
	else if (key == '4')
	{
		MoveType = NULL;
		
		list<ModleChange>::iterator itor = ModleChangeList.begin();

			//행렬 초기화
		for (itor = ModleChangeList.begin(); itor != ModleChangeList.end(); itor++)
		{
			glPopMatrix();
		}
		
		Move4Buffer = true;
		PathCnt = 0;
	}
	
	ModleChangeList.clear();
}

GLvoid Mouse(int button, int state, int x, int y)
{

	if (PathCnt > 4 && Move4Buffer == true)
	{
		MoveType = 4;
		MoveInit = 1;
		Move4Buffer = false;
	}
	else if (Move4Buffer && PathCnt < 5 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Path[PathCnt].x = SceneInit_x + x;
		Path[PathCnt].y =  SceneEnd_y - y;
		PathCnt++;
	}

	if (Move4Buffer && button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		MoveType = 4;
		MoveInit = 1;
		Move4Buffer = false;
	}


	
	glutPostRedisplay();// 현재 윈도우를 refresh하게 한다.
}

void Timerfunction(int value)
{
	if (MoveType == 1)									//직선 이동			//양끝에서 멈추는 현상 픽스 필요
	{
		static int OperateType;				// 1. 정방향 , 2. 역방향
		static double Rocation;
		static int Speed = 50;

		if (MoveInit == 1)
		{
			OperateType = 1;
			TempModleChange.InPut(Translate, 0, SceneInit_x, 0, 0);
			ModleChangeList.push_back(TempModleChange);

			Rocation = SceneInit_x;
			MoveInit = 0;
		}

		else if (OperateType == 1)
		{
			if (Rocation < SceneEnd_x)
			{
				TempModleChange.InPut(Translate, 0, Speed, 0, 0);
				ModleChangeList.push_back(TempModleChange);

				Rocation += Speed;
			}
	
			else OperateType = 2;

		}

		else if (OperateType == 2)
		{

			if (Rocation > SceneInit_x)
			{
				ModleChangeList.pop_back();

				Rocation -= Speed;
			}
			else OperateType = 1;
		}

		
	}

	else if (MoveType == 2)							//회오리 이동

	{
		static int OperateType;					//1. 정방향 , 2. 역방향 
		static double R;
		const double MoveAngle = 5;
		const double MoveR = 1;


		if (MoveInit == 1)
		{
			OperateType = 1;
			TempModleChange.InPut(Translate, 0, 0, 0, 0);
			ModleChangeList.push_back(TempModleChange);

			R = 0;
			MoveInit = 0;
		}

		else if (OperateType == 1)
		{
			if (R < SceneEnd_y)
			{
				TempModleChange.InPut(Rotate, MoveAngle, 0, 0, 1);
				ModleChangeList.push_front(TempModleChange);
				TempModleChange.InPut(Translate, 0, MoveR, 0, 0);
				ModleChangeList.push_back(TempModleChange);

				R += MoveR;
			}

			else OperateType = 2;
			
		}

		else if (OperateType == 2)
		{
			if (R > 0)
			{
				ModleChangeList.pop_front();
				ModleChangeList.pop_back();

				R -= MoveR;
			}
			else OperateType = 1;
		}
	}

	else if (MoveType == 3)							//지그 재그 이동
	{
		static int OperateType;				// 1. 정방향 , 2. 역방향
		static double Rocation;
		static int Speed = 10;
		static int yDirection;
		static int cnt = 0;
			
		if (MoveInit == 1)
		{
			OperateType = 1;
			TempModleChange.InPut(Translate, 0, SceneInit_x, 0, 0);
			ModleChangeList.push_back(TempModleChange);

			Rocation = SceneInit_x;
			yDirection = 1;
			cnt = 0;
			MoveInit = 0;
		}

		else if (OperateType == 1)
		{
			if (Rocation < SceneEnd_x)
			{
				TempModleChange.InPut(Translate, 0, Speed, yDirection * Speed, 0);
				ModleChangeList.push_back(TempModleChange);
				cnt++;

				if (cnt % 3 == 0)
				{
					yDirection *= -1;
				}

				Rocation += Speed;
			}

			else OperateType = 2;

		}

		else if (OperateType == 2)
		{

			if (Rocation > SceneInit_x)
			{
				ModleChangeList.pop_back();

				Rocation -= Speed;
			}
			else
			{
				OperateType = 1;
				yDirection = 1;
				cnt = 0;
			}
		}


	}

	else if (MoveType == 4)							//경로 설정 이동

	{
		static int OperateType;				// 1. 정방향 , 2. 역방향
		static Point Rocation;
		static double Speed = 10;
		static int cnt;
		static int callCnt;

		if (MoveInit == 1)
		{
			OperateType = 1;
			callCnt = 0;
			TempModleChange.InPut(Translate, 0, Path[cnt].x, Path[cnt].y, 0);
			ModleChangeList.push_back(TempModleChange);
			Rocation.x = Path[cnt].x;
			Rocation.y = Path[cnt].y;

			MoveInit = 0;
		}

		else if (OperateType == 1)			
		{
			double GapX = (Path[cnt + 1].x - Path[cnt].x);
			double GapY = (Path[cnt + 1].y - Path[cnt].y);
			double TempMoveX = Speed * GapX / (abs(GapX) + abs(GapY));
			double TempMoveY = Speed * GapY / (abs(GapX) + abs(GapY));

			TempModleChange.InPut(Translate, 0, TempMoveX, TempMoveY, 0);
			ModleChangeList.push_back(TempModleChange);

			Rocation.x += TempMoveX;
			Rocation.y += TempMoveY;
			callCnt++;
		
			if (Path[cnt + 1].x - abs(TempMoveX) < Rocation.x &&  Rocation.x < Path[cnt + 1].x + abs(TempMoveX))
			{
				cout << Rocation.x << ", " << Rocation.y << endl;
				cout << Path[cnt + 1].x << ", " << Path[cnt + 1].y << endl;
				cnt++;
			}
			

			if (cnt + 2 > PathCnt)
			{
				OperateType = 2;
				cnt = 0;
			}
		}

		else if (OperateType == 2)
		{
			if (callCnt == 0)
			{
				OperateType = 1;
				Rocation.x = Path[cnt].x;
				Rocation.y = Path[cnt].y;
			}
			else
			{
				ModleChangeList.pop_back();
				callCnt--;
			}

		}

	}
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, Timerfunction, 1); // 타이머함수 재 설정
}

