#ifndef __MYSTRUCT_H__
#define __MYSTRUCT_H__

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

struct HitBox
{
	Point3d Pos;
	Point3d Size;


	HitBox(){};
	HitBox(Point3d _Pos, Point3d _Size) : Pos(_Pos), Size(_Size){};
	void insert(Point3d _Pos, Point3d _Size){
		Pos = _Pos;
		Size = _Size;
	}
};

#endif //ifndef __MYSTRUCT_H__