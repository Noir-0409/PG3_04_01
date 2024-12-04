#include "Enemy.h"
#include <stdio.h>


Enemy::Enemy(int hp)
{

    hp_ = 183;

    name_ = "garchomp";

}

Enemy::~Enemy()
{

    

}

void Enemy::Damage(int damage)
{

    while (hp_ > 0) {

        printf("%d\n", hp_);

        hp_ -= damage;

        hp_ -= damage;

    }


}

