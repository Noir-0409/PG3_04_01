#include <stdio.h>

int Power(int a) {

	return a * a;

}

float Power(float b) {

	return b * b;

}

int main() {

	int x = 2;

	printf("引数int Power関数 = %d\n", Power(x));

	float y = 2.0f;

	printf("引数float Power関数 = %f\n", Power(y));

	return 0;

}