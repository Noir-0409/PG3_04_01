#include <stdio.h>

int Power(int a) {

	return a * a;

}

float Power(float b) {

	return b * b;

}

int main() {

	int x = 2;

	printf("����int Power�֐� = %d\n", Power(x));

	float y = 2.0f;

	printf("����float Power�֐� = %f\n", Power(y));

	return 0;

}