#pragma once
#include "Canon.h"

class Bullet
{
	Canon canon_;

public:

	Bullet();
	~Bullet();

	void Update(char* keys,char* preKeys);
	void Draw();

};

