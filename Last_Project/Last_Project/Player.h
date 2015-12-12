#ifndef __PLAYER_H__
#define __PLAYER_H__

#define VIEWFRONT 0
#define VIEWRIGHT 90
#define VIEWBACK 180
#define VIEWLEFT 270

struct Point3d
{
	double x = 0;
	double y = 0;
	double z = 0;

	Point3d(){};
	Point3d(double X, double Y, double Z) : x(X), y(Y), z(Z) {};
	void insert(double X, double Y, double Z){
		x = X, y = Y, z = Z;
	}
};

class Player
{
private:
	Point3d Eye;
	Point3d ViewPoint;
	int CameraTotalAngle = 0;
	int ViewMode = VIEWFRONT;

public:
	Player(){};
	Player(Point3d _Eye, Point3d _ViewPoint) : Eye(_Eye), ViewPoint(_ViewPoint){}
	void insertEye(Point3d _Eye);
	void insertViewPoint(Point3d _ViewPoint);
	Point3d returnEye();
	Point3d returnViewPoint();
	void Move(char key);
	void ChangeViewPoint(char key);

};


#endif