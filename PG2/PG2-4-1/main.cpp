#include <stdio.h>

int main() {

	int array[5] = { 5,3,8,12,2 };

	int* p_array = array;

	for (int i = 0; i < 5; i++) {

		printf("%d\n", array[i]);

		printf("%p\n", &array[i]);

	}

	printf("------------------\n");

	for (int i = 0; i < 5; i++) {

		printf("%d\n", p_array[i]);

		printf("%p\n", &p_array[i]);

	}

	return 0;

}