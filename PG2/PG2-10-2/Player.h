#pragma once
class Player
{
	struct Transform {

		int x;
		int y;
		int r;

	};

	Transform transform_;
	int speed_;

public:

	Player();
	~Player();

	void Move(char* keys);
	void Draw();


};

