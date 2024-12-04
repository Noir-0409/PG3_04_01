#pragma once

class Player
{

private:

	int playerPosX_;
	int playerPosY_;
	int playerRadius_;
	int playerSpeed_;
	int respornTimer_;

	int bulletPosX_;
	int bulletPosY_;
	int bulletRadius_;
	int bulletSpeed_;

	int isShot_;

public:

	Player();
	~Player();

	int GetPosX() { return playerPosX_; }
	int GetPosY() { return playerPosY_; }
	int GetRadius() { return playerRadius_; }

	void SetSpeed(int speed) { playerSpeed_ = speed; }

	int GetBulletPosX() { return bulletPosX_; }
	int GetBulletPosY() { return bulletPosY_; }
	int GetBulletRadius() { return bulletRadius_; }

	int GetTimer() { return respornTimer_; }

	void SetBulletSpeed(int bulletSpeed) { bulletSpeed_ = bulletSpeed; }

	void Update(char* keys, char* preKeys); //更新処理の関数

	void Draw(); //描画処理の関数

};

