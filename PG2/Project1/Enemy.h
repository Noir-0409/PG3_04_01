#pragma once
class Enemy
{

public:

	//�����o�ϐ�
	int hp_;

	const char* name_;

	//�����o�֐�
	Enemy(); //�R���X�g���N�^

	~Enemy(); //�f�X�g���N�^

	void Damage(int damage);

};

