#include "Player.h"
#include <Novice.h>

Player::Player()
{

	transform_.x = 100;
	transform_.y = 100;
	transform_.r = 50;
	speed_ = 10;

}

Player::~Player()
{
}


void Player::Move(char* keys)
{

	if (keys[DIK_A]) {

		transform_.x -= speed_;

	}

	if (keys[DIK_D]) {

		transform_.x += speed_;

	}

	if (keys[DIK_W]) {

		transform_.y -= speed_;

	}

	if (keys[DIK_S]) {

		transform_.y += speed_;

	}

}

void Player::Draw()
{

	Novice::DrawEllipse(transform_.x, transform_.y, transform_.r, transform_.r, 0, WHITE, kFillModeSolid);

}

