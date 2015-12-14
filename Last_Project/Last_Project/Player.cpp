#include<iostream>
#include "Player.h"
#include "MyStructs.h"
#include "MyInclude.h"

void Player::insertEye(Point3d _Eye){	Eye = _Eye; }
void Player::insertViewPoint(Point3d _ViewPoint) { ViewPoint = _ViewPoint; }
void Player::insertViewMode(int _ViewMode) { CameraTotalAngle = _ViewMode; ViewMode = _ViewMode; }
Point3d Player::returnEye() { return Eye; }
Point3d Player::returnViewPoint() { return ViewPoint; }
int Player::returnViewMode(){ return ViewMode; }


void Player::Move(char key)
{
	//std::cout << ViewMode << std::endl;

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

bool Player::ChangeViewPoint(char key)
{
	bool change = false;
	if (key == 'd' || key == 'D')
	{
		change = true;
		CameraTotalAngle += VIEWRIGHT;
	}


	if (key == 'a' || key == 'A')
	{
		change = true;
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

	return change;
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
		//std:: cout << "crush!" << std::endl;
	}

	return wall_crush;

}

bool Player::CrushWithEndPoint(HitBox EndPointHitBox)
{
	double left_player = ViewPoint.x - HitBoxSize / 2;
	double bottom_player = ViewPoint.z - HitBoxSize / 2;
	double right_player = ViewPoint.x + HitBoxSize / 2;
	double top_player = ViewPoint.z + HitBoxSize / 2;

	double left_EndPoint = EndPointHitBox.Pos.x - EndPointHitBox.Size.x / 2;
	double bottom_EndPoint = EndPointHitBox.Pos.z - EndPointHitBox.Size.z / 2;
	double	right_EndPoint = EndPointHitBox.Pos.x + EndPointHitBox.Size.x / 2;
	double top_EndPoint = EndPointHitBox.Pos.z + EndPointHitBox.Size.z / 2;

	bool EndPoint_crush = true;
	if (left_player >right_EndPoint) EndPoint_crush = false;
	else if (right_player < left_EndPoint) EndPoint_crush = false;
	else if (top_player <  bottom_EndPoint) EndPoint_crush = false;
	else if (bottom_player > top_EndPoint) EndPoint_crush = false;

	if (EndPoint_crush)
	{

		//std::cout << "crush!" << std::endl;
	}

	return EndPoint_crush;

}


bool Player::CrushWithItem(HitBox ItemHitBox)
{
	double left_player = ViewPoint.x - HitBoxSize / 2;
	double bottom_player = ViewPoint.z - HitBoxSize / 2;
	double right_player = ViewPoint.x + HitBoxSize / 2;
	double top_player = ViewPoint.z + HitBoxSize / 2;

	double left_Item = ItemHitBox.Pos.x - ItemHitBox.Size.x / 2;
	double bottom_Item = ItemHitBox.Pos.z - ItemHitBox.Size.z / 2;
	double	right_Item = ItemHitBox.Pos.x + ItemHitBox.Size.x / 2;
	double top_Item = ItemHitBox.Pos.z + ItemHitBox.Size.z / 2;

	bool Item_crush = true;
	if (left_player >right_Item) Item_crush = false;
	else if (right_player < left_Item) Item_crush = false;
	else if (top_player <  bottom_Item) Item_crush = false;
	else if (bottom_player > top_Item) Item_crush = false;

	if (Item_crush)
	{

		//std::cout << "crush!" << std::endl;
	}

	return Item_crush;

}




void Player::draw()
{
	glPushMatrix();
	glTranslated(Eye.x, Eye.y, Eye.z);
	glutSolidSphere(4, 32, 32);
	glPopMatrix();

}

