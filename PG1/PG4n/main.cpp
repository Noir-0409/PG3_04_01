#include<stdio.h>

int main() {

	int i = 0;
	
	for (int j = 0; j < 10; j++) {

		printf("整数を入力して下さい:%d\n");

		scanf_s("%d", j);

	}

	return 0;
}