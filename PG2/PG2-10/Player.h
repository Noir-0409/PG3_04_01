#pragma once
#include <Struct.h>

class Player
{

public:

	Transform transform_;
	int speed_;

public:

	Player();
	~Player();

	void Move(char* keys);
	void Draw();

};

