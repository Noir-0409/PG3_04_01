#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet()
{

	canon_.x = 0;
	canon_.y = 0;
	canon_.r = 10;
	canon_.speed = 5;

}

Bullet::~Bullet()
{
}

void Bullet::Update(char* keys,char* preKeys)
{

	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {

		canon_.isShot = 1;

	}

	if (canon_.isShot == 1) {

		canon_.y -= canon_.speed;

	}

	if (canon_.y <= 0) {

		canon_.isShot = 0;

	}
}

void Bullet::Draw()
{
	if (canon_.isShot == 0) {

		Novice::DrawEllipse(canon_.x, canon_.y, canon_.r, canon_.r, 0, WHITE, kFillModeSolid);
	
	}
}
