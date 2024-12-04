#include <stdio.h>

int main() {

	int state = 0b1010;

	int a = 0b1000; // 眠り

	int b = 0b0100; // 石化

	int c = 0b0010; // 毒

	int d = 0b0001; // 戦闘不能

	printf("state=%d\n", state);

	if (state & a) {

		printf("眠り\n");

	}

	if (state & b) {

		printf("石化\n");

	}

	if (state & c) {

		printf("毒\n");

	}

	if (state & d) {

		printf("戦闘不能\n");
	}

	

	return 0;

}