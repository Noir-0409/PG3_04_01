#pragma once
class Bullet
{

private:

	int bulletPosX_;
	int bulletPosY_;
	int bulletRadius_;
	int bulletSpeed_;
	int isShot_;

public:

	Bullet();
	~Bullet();

	void Update();

	void Draw();

};

