#include "Enemy.h"
#include "Novice.h"

Enemy::Enemy()
{
	enemyPosX_ = 640;
	enemyPosY_ = 100;
	enemyRadius_ = 40;
	enemySpeed_ = 7;

}

Enemy::~Enemy()
{
}

void Enemy::SetPos(int x, int y)
{
}

void Enemy::Initalize()
{
}

void Enemy::Update()
{

	if (enemyIsAlive_) {

		enemyPosX_ += enemySpeed_;

	}

	if (enemyPosX_ >= 1280) {

		enemySpeed_ *= -1;

	} else if (enemyPosX_ <= 0) {

		enemyPosX_ *= -1;

	}

}

void Enemy::Draw()
{

	if (enemyIsAlive_) {

		Novice::DrawEllipse(enemyPosX_, enemyPosY_, enemyRadius_, enemyRadius_, 0.0f, RED, kFillModeSolid);

	}

}
