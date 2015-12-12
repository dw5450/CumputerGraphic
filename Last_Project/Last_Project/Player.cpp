#include<iostream>
#include "Player.h"
#include "MyStructs.h"

void Player::insertEye(Point3d _Eye){	Eye = _Eye; }
void Player::insertViewPoint(Point3d _ViewPoint) { ViewPoint = _ViewPoint; }
Point3d Player::returnEye() { return Eye; }
Point3d Player::returnViewPoint() { return ViewPoint; }


void Player::Move(char key)
{

	oldEye = Eye;

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

bool Player::CrushWithWall(HitBox WallHitBox)
{
	double left_player = ViewPoint.x - HitBoxSize / 2;
	double bottom_player = ViewPoint.z - HitBoxSize / 2;
	double right_player = ViewPoint.x + HitBoxSize / 2;
	double top_player = ViewPoint.z + HitBoxSize / 2;

	double left_Wall = WallHitBox.Pos.x - WallHitBox.Size.x / 2;
	double bottom_Wall = WallHitBox.Pos.z - WallHitBox.Size.z / 2;
	double	right_Wall = WallHitBox.Pos.x + WallHitBox.Size.x / 2;
	double top_Wall = WallHitBox.Pos.z + WallHitBox.Size.z / 2;

	bool wall_crush = true;
	if (left_player > right_Wall) wall_crush = false;
	else if (right_player < left_Wall) wall_crush = false;
	else if (top_player < bottom_Wall) wall_crush = false;
	else if (bottom_player > top_Wall) wall_crush = false;

	if (wall_crush)
	{
		Eye = oldEye;
		ChangeViewPoint(NULL);
		std:: cout << "crush!" << std::endl;
	}

	return wall_crush;

}