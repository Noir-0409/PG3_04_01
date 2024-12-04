#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Dice.h"

int main() {

	srand(time(nullptr));

	Dice* dice1 = new Dice(6); //インスタンス

	Dice* dice2 = new Dice(100);

	int number1 = dice1->Roll();

	int number2 = dice1->Roll();

	delete dice1; //解放

	delete dice2;

	return 0;

}