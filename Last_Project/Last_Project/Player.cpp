#include<iostream>
#include "Player.h"

void Player::insertEye(Point3d _Eye){	Eye = _Eye; }
void Player::insertViewPoint(Point3d _ViewPoint) { ViewPoint = _ViewPoint; }
Point3d Player::returnEye() { return Eye; }
Point3d Player::returnViewPoint() { return ViewPoint; }


void Player::Move(char key)
{
	if (key == 'w' || key == 'W')
	{
		if (ViewMode == VIEWLEFT)
			Eye.insert(Eye.x - 1, Eye.y, Eye.z);

		if (ViewMode == VIEWRIGHT)
			Eye.insert(Eye.x + 1, Eye.y, Eye.z);

		if (ViewMode == VIEWFRONT)
			Eye.insert(Eye.x, Eye.y, Eye.z - 1);

		if (ViewMode == VIEWBACK)
			Eye.insert(Eye.x, Eye.y, Eye.z + 1);
	}

	if (key == 's' || key == 'S')
	{
		if (ViewMode == VIEWLEFT)
			Eye.insert(Eye.x + 1, Eye.y, Eye.z);

		if (ViewMode == VIEWRIGHT)
			Eye.insert(Eye.x - 1, Eye.y, Eye.z);

		if (ViewMode == VIEWFRONT)
			Eye.insert(Eye.x, Eye.y, Eye.z + 1);

		if (ViewMode == VIEWBACK)
			Eye.insert(Eye.x, Eye.y, Eye.z - 1);
	}
}

void Player::ChangeViewPoint(char key)
{
	if (key == 'd' || key == 'D')
	{
		CameraTotalAngle += VIEWRIGHT;
	}


	if (key == 'a' || key == 'A')
	{
		CameraTotalAngle += VIEWLEFT;
	}

	ViewMode = CameraTotalAngle % 360;

	if (ViewMode == VIEWLEFT)
		ViewPoint.insert(Eye.x - 1, Eye.y, Eye.z);

	if (ViewMode == VIEWRIGHT)
		ViewPoint.insert(Eye.x + 1, Eye.y, Eye.z);

	if (ViewMode == VIEWFRONT)
		ViewPoint.insert(Eye.x, Eye.y, Eye.z - 1);

	if (ViewMode == VIEWBACK)
		ViewPoint.insert(Eye.x, Eye.y, Eye.z + 1);
}