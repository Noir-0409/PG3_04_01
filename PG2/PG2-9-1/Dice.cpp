#include "Dice.h"
#include <stdlib.h>

Dice::Dice(int diceMax)
{

    kDiceMax = diceMax;

}

Dice::~Dice()
{
}

int Dice::Roll()
{
    int number = rand() % kDiceMax + 1;

    return number;
}
