

#include<glut.h>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<Windows.h>
#include<list>
#include<algorithm>
#include <stdio.h> // 헤더 파일 삽입
#include <windows.h> // 비트맵 파일 관렦 자료 저장

#define PI   3.14159265359

using namespace std;

//필요한 구조체 선언
struct Point3d
{
	double x = 0;
	double y = 0;
	double z = 0;

	void insert(double X, double Y, double Z){
		x = X, y = Y, z = Z;
	}
};


//필요한 변수 선언

double CameraXangle;            //x축 각도
double CameraYangle;            //y축 각도
double CameraZangle;            //z축 각도

double ViewingX;
double ViewingY;
double ViewingZ;

GLubyte *pBytes; // 데이터를 가리킬 포인터
GLuint textures[1];
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수

//글로벌 조명 설정용 변수
GLfloat GlobalAmbientLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };

//조명 0 설정용 변수
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat DiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0f };
GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos0[] = { 0.0, 0, 0, 1.0 };

//컬러 설정용 변수
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//필요한 함수 선언



//면을 그리는 함수
void drawFace(Point3d vertax_pos[], Point3d vertax_color[], int vertax[], int vertax_num, bool outer_ctr)         //도형의 모든 점 좌표, 도형의 모든 점 색깔, 현재 면의 점 index, 현재 면의 점 갯수, 법선 벡터 설정  
{
	Point3d vector_A;
	vector_A.insert(vertax_pos[vertax[0]].x - vertax_pos[vertax[1]].x,
		vertax_pos[vertax[0]].y - vertax_pos[vertax[1]].y,
		vertax_pos[vertax[0]].z - vertax_pos[vertax[1]].z);

	Point3d vector_B;
	vector_B.insert(vertax_pos[vertax[2]].x - vertax_pos[vertax[1]].x,
		vertax_pos[vertax[2]].y - vertax_pos[vertax[1]].y,
		vertax_pos[vertax[2]].z - vertax_pos[vertax[1]].z);

	Point3d outer;
	outer.insert(vector_A.y * vector_B.z - vector_A.z * vector_B.y,
		-(vector_A.x * vector_B.z - vector_A.z * vector_B.x),
		vector_A.x * vector_B.y - vector_A.y * vector_B.x);


	if (vertax_num == 3)
		glBegin(GL_TRIANGLES);
	else if (vertax_num == 4)
		glBegin(GL_QUADS);

	//법선 벡터 설정

	if (outer_ctr == true)
		glNormal3f(outer.x, outer.y, outer.z);


	//면 그리기
	for (int i = 0; i < vertax_num; i++)
	{
		for (int j = 0; j < 100; j++)
			if (vertax[i] == j)
			{
				glColor3f(vertax_color[j].x, vertax_color[i].y, vertax_color[i].z);
				glVertex3d(vertax_pos[j].x, vertax_pos[j].y, vertax_pos[j].z);
				break;
			}
	}

	glEnd();
}
//need_fix
//피라미드를 생성해 주는 함수
void drawPramid(Point3d pramid_dots_pos[5], Point3d pramid_dots_color[5], bool outer_ctr)//피라미드 점 위치 5개, 피라미드 점 색깔 5개, 법석 벡터 설정
{
	int front_face[] = { 0, 1, 4 };      //정면 면
	int left_face[] = { 0, 2, 1 };      //왼쪽 면
	int back_face[] = { 0, 3, 2 };      //뒷쪽 면 
	int right_face[] = { 0, 4, 3 };      //오른쪽 면
	int bottom_face[] = { 1, 4, 3, 2 };   //밑면


	drawFace(pramid_dots_pos, pramid_dots_color, front_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, left_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, back_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, right_face, 3, outer_ctr);
	drawFace(pramid_dots_pos, pramid_dots_color, bottom_face, 4, outer_ctr);

}
//need_fix_end


//각도 계산을 위한 라디안 함수
double getRadian(double _num)         //현제 각도 return 각도의 라디안값
{
	return _num * (PI / 180);
}

//현재 위치에 원을 그려주는 함수
void drawRotate(double _r){            //원의 반지름 입력 
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 120; ++i){
		glVertex2f(_r * cos(3 * i * (PI / 180)), _r * sin(3 * i * (PI / 180)));
	}
	glEnd();
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fopen_s(&fp, filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	cout << ">" <<endl;
	// 파일이 BMP 파일인지 확인핚다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 핛당을 핚다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 핛당핚다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장핚다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

///화면 컨트롤을 위한 기본 함수 선언
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);
double getRadian(double _num);

void initialize()

{
	CameraXangle = 0;            //카메라 x축 각도
	CameraYangle = 0;            //카메라 y축 각도
	CameraZangle = 0;            //카메라 z축 각도

	ViewingX = 0;               //카메라 x축 위치
	ViewingY = 0;               //카메라 y축 위치
	ViewingZ = -10;               //카메라 z축 위치

	GLubyte *m_bitmap;
	BITMAPINFO *m_bitInfo;
	GLfloat xoffset, yoffset;
	xoffset = 1;
	yoffset = 1;
	GLfloat xscale = 2.0, yscale = 2.0;
	m_bitmap = LoadDIBitmap("banana.BMP", &m_bitInfo);
	glRasterPos2f(xoffset, yoffset);
	glPixelZoom(xscale, yscale);
	glDrawPixels(179, 158, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap);
	
	
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
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);      // 원근 투영을 사용하는 경우

	glPushMatrix();
	glTranslated(ViewingX, ViewingY, ViewingZ);
	glRotated(CameraXangle, 1.0, 0.0, 0.0);
	glRotated(CameraYangle, 0.0, 1.0, 0.0);
	glRotated(CameraZangle, 0.0, 0.0, 1.0);


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

	glPushMatrix();

	//조명 0 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);

	//조명0 on
	glEnable(GL_LIGHT0);


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
	glTranslated(0.0, -4, 0.0);
	glScaled(1.0, 0.01, 1.0);

	glutSolidCube(10);

	glPopMatrix();


	// 6개의 이미지 텍스처 매핑을 핚다.
	//glGenTextures(1, textures);
	//텍스처와 객체를 결합핚다. --- (1)
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	////이미지 로딩을 핚다. --- (2)
	//pBytes = LoadDIBitmap("banana.BMP", &info);


	////텍스처 설정 정의를 핚다. --- (3)

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 179, 158, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);


	////텍스처 파라미터 설정 --- (4)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//// 나머지 n-1개의 텍스처에도 (1) ~ (4)까지의 과정을 짂행하여 텍스처를 설정핚다.
	//// 텍스처 모드 설정
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	//// 텍스처 매핑 홗성화
	//glEnable(GL_TEXTURE_2D);
	// 텍스처를 객체에 맵핑
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
		glVertex3d(-1, -1, 0);
		glVertex3d(-1, 1, 0);
		glVertex3d(1, 1, 0);
		glVertex3d(1, -1, 0);
	glEnd();



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

	if (key == '<' || key == ',')
		CameraYangle += 1.0;
	else if (key == '>' || key == '.')
		CameraYangle -= 1.0;


	else if (key == 'i')
		initialize();

	cout << "(" << ViewingX << ", " << ViewingY << ", " << ViewingZ << ")" << endl;

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