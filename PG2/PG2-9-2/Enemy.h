#pragma once
class Enemy
{

public:

	Enemy(); //コンストラクタ

	~Enemy(); //デストラクタ

	void Damage(int damage); //ダメージ

	int hp_; // HP

	const char* name_;

};

