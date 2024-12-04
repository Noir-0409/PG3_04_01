#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy()
{

	enemyPosX_ = 640;
	enemyPosY_ = 100;
	enemyRadius_ = 30;
	enemySpeed_ = 7;
	respornTimer_ = 30;

}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//更新処理
	enemyPosX_ += enemySpeed_;

	if (enemyPosX_ >= 1280) {

		enemySpeed_ *= -1;

	} 

	if (enemyPosX_ <= 0) {

		enemySpeed_ *= -1;

	}
}

void Enemy::Draw()
{
	//描画処理
	Novice::DrawEllipse(enemyPosX_, enemyPosY_, enemyRadius_, enemyRadius_, 0.0f, BLUE, kFillModeSolid);
}
