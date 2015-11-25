

#include<glut.h>
#include<iostream>
#include <stdio.h> 
#include <windows.h>

#define PI   3.14159265359

using namespace std;

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if (fopen_s(&fp, filename, "rb") == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
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

//글로벌 조명 설정용 변수
GLfloat GlobalAmbientLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };

//조명 0 설정용 변수
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat DiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0f };
GLfloat SpecularLight0[] = { 0, 0, 0, 1.0 };
GLfloat LightPos0[] = { -100.0, 100, 0, 0.0 };

//컬러 설정용 변수
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


//사용자 컨트롤 변수

// 현제 선택된 도형들 index

int select_num;

//현제 선택된 도형들의 블랜딩 값

double blend_coefficient[9];

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장핛 변수
GLuint texture_object[3]; // 텍스처 이름


///화면 컨트롤을 위한 기본 함수 선언
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Timerfunction(int value);

void initialize()

{

	select_num = 0;
	for (int i = 0; i < 9; i++)
		blend_coefficient[i] = 0.2 + 0.07 * i;


	//n개의 이미지 텍스처 매핑을 핚다.
	glGenTextures(1, texture_object);
	//텍스처와 객체를 결합핚다. --- (1)
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	//이미지 로딩을 핚다. --- (2)
	pBytes = LoadDIBitmap("image_1.bmp", &info );
	//텍스처 설정 정의를 핚다. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 32, 0, GL_BGR_EXT,GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	

}

void main(int argc, char *argv[])
{
	//초기화 함수들 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 0); //    윈도우의 위치지정 
	glutInitWindowSize(600, 600); // 윈도우의 크기 지정 
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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'black' 로 지정 
	glClear( GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기 

	//모델링 변환 : 모델 위치 설정

	//조명 효과 설정
	glEnable(GL_LIGHTING);                                    //조명 사용 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbientLight);         //전역 조명 모델 설정

	//물체 색 효과 속성 설정
	glEnable(GL_COLOR_MATERIAL);                              //컬러 트랙킹 설정(glColor3f사용 설정)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //재질 속성 설정(물체 색 효과 설정)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //하이라이트 색깔
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //하이라이트 계수
	glShadeModel(GL_SMOOTH);          
	//부드러운 쉐이딩
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);

	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);

	glTexEnvf(GL_TEXTURE_ENV, GL_DECAL, GL_MODULATE);
	// 텍스처 매핑 홗성화
	glEnable(GL_TEXTURE_2D);
	// 텍스처를 객체에 맵핑
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		glVertex3f(100, -100, 0);
		glVertex3f(-100, -100, 0);
		
	glEnd();
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (3 * i + j == select_num)
			{
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // 그리기 색을 'white' 으로 지정
				glRectf(200 * j, -200 * i, 200 * (j + 1), -200 * (i + 1));

				glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // 그리기 색을 'black' 으로 지정
				glRectf(200 * j + 10, -200 * i - 10, 200 * (j + 1) - 10, -200 * (i + 1) + 10);
			}


			glColor4f(0.0f, 0.0f, 1.0f, blend_coefficient[3 * i + j]); // 그리기 색을 'blue' 으로 지정
			glPushMatrix();
				glTranslated(115 + 200 * j, -150 - 200 * i, 0);
				glutSolidSphere(45, 32, 32);
			glPopMatrix();

			glColor4f(1.0f, 0.0f, 0.0f, blend_coefficient[3 * i + j]); // 그리기 색을 'red' 으로 지정
			glPushMatrix();
				glTranslated(70 + 200 * j, -150 - 200 * i, 0);
				glutSolidTeapot(45);
			glPopMatrix();

			glColor4f(0.0f, 1.0f, 0.0f, blend_coefficient[3 * i + j]); // 그리기 색을 'green' 으로 지정
			glPushMatrix();
				glTranslated(140 + 200 * j, -150 - 200 * i, 0);
				glRotated(-90, 1, 0, 0);
				glutSolidCone(50, 100, 32, 32);
			glRotated(90, 1, 0, 0);
			glPopMatrix();

		}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{

	glViewport(0, 0, w, h);
	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수


	glOrtho(0, 600, -600, 0, -100.0, 100.0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd' || key == 'D'){
		if (select_num < 8)
			select_num++;
	}

	if (key == 'a' || key == 'A'){
		if (select_num > 0)
			select_num--;
	}

	if (key == 'w' || key == 'W'){
		if (select_num - 3 > 0)
			select_num -= 3;
	}

	if (key == 's' || key == 'S'){
		if (select_num + 3 < 8)
			select_num += 3;
	}

	if (key == '+' || key == '=')
		blend_coefficient[select_num] += 0.1;

	if (key == '-' || key == '_')
		blend_coefficient[select_num] -= 0.1;


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