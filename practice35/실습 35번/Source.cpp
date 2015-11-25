

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
	// ���̳ʸ� �б� ���� ������ ����
	if (fopen_s(&fp, filename, "rb") == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ������.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� ������ ����.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� ��������.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� ��������.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

//�۷ι� ���� ������ ����
GLfloat GlobalAmbientLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };

//���� 0 ������ ����
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat DiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0f };
GLfloat SpecularLight0[] = { 0, 0, 0, 1.0 };
GLfloat LightPos0[] = { -100.0, 100, 0, 0.0 };

//�÷� ������ ����
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


//����� ��Ʈ�� ����

// ���� ���õ� ������ index

int select_num;

//���� ���õ� �������� ���� ��

double blend_coefficient[9];

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
GLuint texture_object[3]; // �ؽ�ó �̸�


///ȭ�� ��Ʈ���� ���� �⺻ �Լ� ����
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


	//n���� �̹��� �ؽ�ó ������ ����.
	glGenTextures(1, texture_object);
	//�ؽ�ó�� ��ü�� ��������. --- (1)
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	//�̹��� �ε��� ����. --- (2)
	pBytes = LoadDIBitmap("image_1.bmp", &info );
	//�ؽ�ó ���� ���Ǹ� ����. --- (3)
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 32, 0, GL_BGR_EXT,GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	

}

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 0); //    �������� ��ġ���� 
	glutInitWindowSize(600, 600); // �������� ũ�� ���� 
	glutCreateWindow("��ǻ�� �׷��� �⺻ �ڵ� by 2014180026"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �Լ��� ����
	glutMouseFunc(Mouse); // �ܼ� ���콺 �Է� �Լ��� ����
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ���� 

	initialize();

	glutMainLoop();

}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	//���� ��ȯ : ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'black' �� ���� 
	glClear( GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	//�𵨸� ��ȯ : �� ��ġ ����

	//���� ȿ�� ����
	glEnable(GL_LIGHTING);                                    //���� ��� ����
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbientLight);         //���� ���� �� ����

	//��ü �� ȿ�� �Ӽ� ����
	glEnable(GL_COLOR_MATERIAL);                              //�÷� Ʈ��ŷ ����(glColor3f��� ����)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //���� �Ӽ� ����(��ü �� ȿ�� ����)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //���̶���Ʈ ����
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //���̶���Ʈ ���
	glShadeModel(GL_SMOOTH);          
	//�ε巯�� ���̵�
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);

	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);

	glTexEnvf(GL_TEXTURE_ENV, GL_DECAL, GL_MODULATE);
	// �ؽ�ó ���� �R��ȭ
	glEnable(GL_TEXTURE_2D);
	// �ؽ�ó�� ��ü�� ����
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
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'white' ���� ����
				glRectf(200 * j, -200 * i, 200 * (j + 1), -200 * (i + 1));

				glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // �׸��� ���� 'black' ���� ����
				glRectf(200 * j + 10, -200 * i - 10, 200 * (j + 1) - 10, -200 * (i + 1) + 10);
			}


			glColor4f(0.0f, 0.0f, 1.0f, blend_coefficient[3 * i + j]); // �׸��� ���� 'blue' ���� ����
			glPushMatrix();
				glTranslated(115 + 200 * j, -150 - 200 * i, 0);
				glutSolidSphere(45, 32, 32);
			glPopMatrix();

			glColor4f(1.0f, 0.0f, 0.0f, blend_coefficient[3 * i + j]); // �׸��� ���� 'red' ���� ����
			glPushMatrix();
				glTranslated(70 + 200 * j, -150 - 200 * i, 0);
				glutSolidTeapot(45);
			glPopMatrix();

			glColor4f(0.0f, 1.0f, 0.0f, blend_coefficient[3 * i + j]); // �׸��� ���� 'green' ���� ����
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
	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ�


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


	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

GLvoid Mouse(int button, int state, int x, int y)
{




	glutPostRedisplay();// ���� �����츦 refresh�ϰ� �Ѵ�.
}

void Timerfunction(int value)
{

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}