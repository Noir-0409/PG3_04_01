#include "Bullet.h"
#include "Novice.h"

Bullet::Bullet()
{
	bulletPosX_ = 0;
	bulletPosY_ = 0;
	bulletSpeed_ = 10;
	bulletRadius_ = 20;
	isShot_ = false;

}

Bullet::~Bullet()
{
}

void Bullet::Update()
{

	if (isShot_) {

		bulletPosY_ -= bulletSpeed_;

	}

	if (bulletPosY_ << -20) {

		isShot_ = false;

	}

}

void Bullet::Draw()
{

	if (isShot_) {

		Novice::DrawEllipse(bulletPosX_, bulletPosY_, bulletRadius_, bulletRadius_, 0.0f, BLUE, kFillModeSolid);

	}

}
