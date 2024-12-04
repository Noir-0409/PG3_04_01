#include "Player.h"
#include "Novice.h"

Player::Player()
{

	playerPosX_ = 640;
	playerPosY_ = 450;
	playerRadius_ = 40;
	playerSpeed_ = 7;

}

Player::~Player()
{
}

void Player::Initalize()
{
}

void Player::Update(char* keys, char* prekeys)
{

	if (keys[DIK_A]) {

		playerPosX_ -= playerSpeed_;

	} else if (keys[DIK_D]) {

		playerPosX_ += playerSpeed_;

	} else if (keys[DIK_W]) {

		playerPosY_ -= playerSpeed_;

	} else if (keys[DIK_S]) {

		playerPosY_ += playerSpeed_;

	}

}

void Player::Draw()
{

	Novice::DrawEllipse(playerPosX_, playerPosY_, playerRadius_, playerRadius_, 0.0f, WHITE, kFillModeSolid);

}
