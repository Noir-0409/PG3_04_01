#include "Enemy.h"
#include <stdio.h>

Enemy::Enemy()
{

	hp_ = 183;

	name_ = "garchomp";

}

Enemy::~Enemy()
{

	printf("%s‚Í“|‚ê‚½\n", name_);

}

void Enemy::Damage(int damage)
{

	hp_ -= damage;

	printf("%s\n", name_);

	printf("HP:%d\n", hp_);

}
