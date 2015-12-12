#include<glut.h>
#include<iostream>
#include <list>
#include <cstdio>
#include "Player.h"
#include "Wall.h"

#define PI   3.14159265359


using namespace std;

//�ʿ��� ���� ����

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

//�۷ι� ���� ������ ����
GLfloat GlobalAmbientLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };

//���� 0 ������ ����
GLfloat AmbientLight0[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat DiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0f };
GLfloat SpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat LightPos0[] = { 0.0, 0, 0, 1.0 };

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

	//�÷��̾� �� ����
	Player1.insertEye(Point3d(0.0, 0.0, 30.0));
	Player1.insertViewPoint(Point3d(0.0, 0.0, 29.0));


	//ù��° �� ����
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
	gluLookAt(Eye.x, Eye.y, Eye.z, ViewPoint.x, ViewPoint.y, ViewPoint.z, 0.0, 1.0, 0.0);      // ���� ������ ����ϴ� ���
	
	//�𵨸� ��ȯ : �� ��ġ ����
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                        // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               // ������ ������ ��ü�� ĥ�ϱ�, ���� ����


	//���� ȿ�� ����
	glEnable(GL_LIGHTING);                                    //���� ��� ����
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GlobalAmbientLight);         //���� ���� �� ����


	//��ü �� ȿ�� �Ӽ� ����
	glEnable(GL_COLOR_MATERIAL);                              //�÷� Ʈ��ŷ ����(glColor3f��� ����)
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);               //���� �Ӽ� ����(��ü �� ȿ�� ����)
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);                  //���̶���Ʈ ����
	glMateriali(GL_FRONT, GL_SHININESS, 64);                     //���̶���Ʈ ���
	glShadeModel(GL_SMOOTH);                                 //�ε巯�� ���̵�

	//���� ����, �ø� ����
	glEnable(GL_DEPTH_TEST);                                 //���� ���� 
	//glEnable(GL_CULL_FACE);                                 //�ø�
	//glFrontFace(GL_CCW);                                    //�ո� -> ccw(�ݽð� ����) ����

	//���� 0 ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);

	//����0 on
	glEnable(GL_LIGHT0);

	glPushMatrix();



	//x��   ������
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(1, 0, 0);
	glEnd();

	//y��   �ʷϻ�
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 1, 0);
	glEnd();


	//z��   //�Ķ���
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 1);
	glEnd();


	//�عٴ�  //�Ķ���
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
	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ�


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

