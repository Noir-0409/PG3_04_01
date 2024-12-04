#pragma once
class Enemy
{

public:

	//メンバ変数
	int hp_;

	const char* name_;

	//メンバ関数
	Enemy(); //コンストラクタ

	~Enemy(); //デストラクタ

	void Damage(int damage);

};

