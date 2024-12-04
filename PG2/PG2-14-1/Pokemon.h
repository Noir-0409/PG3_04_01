#pragma once
class Pokemon
{

private:

	int num;

public:

	Pokemon(int x = 0) { num = x; }

	Pokemon& operator=(const Pokemon& obj) {

		num = obj.num;

		return *this;

	}

};

