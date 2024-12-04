#include <stdio.h>
#include "Enemy.h"

int main() {

	Enemy* e1 = new Enemy;

	int number1 = e1->hp_;

	int number2 = 50;

	while (number1>0) {

		printf("%d\n", number1);

		number1 -= number2;

	}

	if (number1 <= 0) {

		delete e1;

	}

	return 0;

}