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

//�ʿ��� ���� ����

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

//�۷ι� ���� ������ ����
GLfloat GlobalAmbientLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };

//���� 0 ������ ����
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat DiffuseLight0[] = { 0.7, 0.7, 0.7, 1.0f };
GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos0[] = { 0, 0, 0, 1.0 };

//���� 0 ������ ����
GLfloat AmbientLight1[] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat DiffuseLight1[] = { 0.7, 0.7, 0.7, 1.0f };
GLfloat SpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos1[] = { 50, 10, -50, 1.0 };


//�÷� ������ ����
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
	//�� ��� ����

	ViewMode = PLAY;
	//�÷��̾� �� ����
	Player1.insertEye(Point3d(0.0, 0.0, 30.0));
	Player1.insertViewPoint(Point3d(0.0, 0.0, 29.0));


	//ù��° �� ����
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
	//�ʱ�ȭ �Լ��� 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 0); //    �������� ��ġ���� 
	glutInitWindowSize(700, 700); // �������� ũ�� ���� 
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);               // ���� ������ ����ϴ� ���
	gluPerspective(60.0, 1.0, 1.0, 1000.0);                     // ���� ������ ����ϴ� ���

	Point3d Eye = Player1.returnEye();
	Point3d ViewPoint = Player1.returnViewPoint();

	if (ViewMode == PLAY)
		gluLookAt(Eye.x, Eye.y + 0.1, Eye.z, ViewPoint.x, ViewPoint.y, ViewPoint.z, 0.0, 1.0, 0.0);      // ���� ������ ����ϴ� ���

	else if (ViewMode == VIEW_MAP){

		gluLookAt(50, 100.0, -50, 49, -1, -50, 0.0, 1.0, 0.0);      // ���� ������ ����ϴ� ���
		glPushMatrix();

	}
	
	//�𵨸� ��ȯ : �� ��ġ ����
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // ������ ������ ��ü�� ĥ�ϱ�, ���� ����


	//���� ȿ�� ����
	glEnable(GL_LIGHTING);                                    //���� ��� ����


	//��ü �� ȿ�� �Ӽ� ����
	glEnable(GL_COLOR_MATERIAL);                              //�÷� Ʈ��ŷ ����(glColor3f��� ����)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //���� �Ӽ� ����(��ü �� ȿ�� ����)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //���̶���Ʈ ����
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //���̶���Ʈ ���
	glShadeModel(GL_FLAT);                                 //�ε巯�� ���̵�

	//���� ����, �ø� ����
	glEnable(GL_DEPTH_TEST);                                 //���� ���� 
	glEnable(GL_CULL_FACE);                                 //�ø�
	glFrontFace(GL_CCW);                                    //�ո� -> ccw(�ݽð� ����) ����
	//�عٴ�  //�Ķ���


	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos1);

	//����0 on
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

	//���� 0 ����
	
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{


	glViewport(0, 0, w, h);
	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ�


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

