#pragma once
class Enemy
{

public:

	Enemy(); //�R���X�g���N�^

	~Enemy(); //�f�X�g���N�^

	void Damage(int damage); //�_���[�W

	int hp_; // HP

	const char* name_;

};

