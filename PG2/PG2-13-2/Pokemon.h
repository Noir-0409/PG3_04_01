#pragma once

class Pokemon
{

public:

	Pokemon(const char* name);
	
	~Pokemon();

	Pokemon(const Pokemon& obj);

private:

	const char* name;

};

