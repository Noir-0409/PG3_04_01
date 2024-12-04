#pragma once
class Enemy
{

private:

	int enemyPosX_;
	int enemyPosY_;
	int enemyRadius_;
	int enemySpeed_;

public:

	Enemy();
	~Enemy();

	int GetPosX() { return enemyPosX_; }
	int GetPosY() { return enemyPosY_; }

	void SetPos(int x, int y);

	void Initalize(); //初期化用の関数

	void Update(); //更新処理の関数

	void Draw(); //描画処理の関数

};

