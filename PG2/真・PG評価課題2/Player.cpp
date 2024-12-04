#include "Player.h"
#include <Novice.h>

Player::Player()
{

	playerPosX_ = 640;
	playerPosY_ = 500;
	playerSpeed_ = 7;
	playerRadius_ = 30;
	respornTimer_ = 30;

	bulletPosX_ = 0;
	bulletPosY_ = 0;
	bulletSpeed_ = 15;
	bulletRadius_ = 20;

	isShot_ = false;

}

Player::~Player()
{
}

void Player::Update(char* keys, char* preKeys)
{
	//更新処理
	if (keys[DIK_A]) {

		playerPosX_ -= playerSpeed_;

	}

	if (keys[DIK_D]) {

		playerPosX_ += playerSpeed_;

	}
	
	if (keys[DIK_W]) {

		playerPosY_ -= playerSpeed_;

	}
	
	if (keys[DIK_S]) {

		playerPosY_ += playerSpeed_;

	}

	if (isShot_ == false) {

		if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==false) {

			isShot_ = true;

			bulletPosX_ = playerPosX_;
			bulletPosY_ = playerPosY_;

		}

	}

	if (isShot_) {

		bulletPosY_ -= bulletSpeed_;

		if (bulletPosY_ <= -30) {

			isShot_ = false;

		}

	}

}

void Player::Draw()
{
	//描画処理
	Novice::DrawEllipse(playerPosX_, playerPosY_, playerRadius_, playerRadius_, 0.0f, WHITE, kFillModeSolid);

	if (isShot_) {

		Novice::DrawEllipse(bulletPosX_, bulletPosY_, bulletRadius_, bulletRadius_, 0.0f, RED, kFillModeSolid);

	}
	

}