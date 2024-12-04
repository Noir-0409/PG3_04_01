#pragma once
class Dice
{

public:

	Dice(int diceMax); //コンストラクタ

	~Dice(); //デストラクタ

	int Roll();

	int kDiceMax; //出目の最大値

};

