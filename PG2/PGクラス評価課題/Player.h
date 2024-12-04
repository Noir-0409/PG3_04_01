#pragma once
class Player
{

private:

	int playerPosX_;
	int playerPosY_;
	int playerRadius_;
	int playerSpeed_;

public:

	Player();
	~Player();

	int GetPosX() { return playerPosX_; }
	int GetPosY() { return playerPosY_; }

	void setSpeed(int speed) { playerSpeed_ = speed; }

	void Initalize(); //初期化用の関数

	void Update(char* keys, char* prekeys); //更新処理の関数

	void Draw(); //描画処理の関数

};

