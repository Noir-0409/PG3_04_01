#pragma once
class Enemy
{
private:

	int enemyPosX_;
	int enemyPosY_;
	int enemyRadius_;
	int enemySpeed_;
	int respornTimer_;
	
	int isAlive_;

public:

	Enemy();
	~Enemy();

	int GetPosX() { return enemyPosX_; }
	int GetPosY() { return enemyPosY_; }

	int GetRadius() { return enemyRadius_; }

	int GetTimer() { return respornTimer_; }

	void Update(); //更新処理の関数

	void Draw(); //描画処理の関数

};

