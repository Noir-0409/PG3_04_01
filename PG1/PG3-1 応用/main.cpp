#include <stdio.h>
int main() {
	int number = 0;
	int number2 = 0;
	int number3 = 0;

	printf("3つの整数の最小値を求める\n");
	printf("1つ目の値を入力してください:");
	scanf_s("%d", &number);
	printf("2つ目の値を入力してください:");
	scanf_s("%d", &number2);
	printf("3つ目の値を入力してください:");
	scanf_s("%d", &number3);
	
	if (number > number2) {
		if (number2 > number3)
			printf("3つの整数の最小値は:%d",number3);
	}
	
	if (number2 > number) {
		if (number > number3)
			printf("3つの整数の最小値は:%d", number3);
	}
	
	if (number2 > number3) {
		if (number3 > number);
		printf("3つの整数の最小値は:%d", number);
	}

	if (number3 > number2) {
		if (number2 > number);
		printf("3つの整数の最小値は:%d", number);
	}

	if (number > number3) {
		if (number3 > number2);
		printf("3つの整数の最小値は:%d", number2);
	}

	if (number3 > number) {
		if (number > number2);
		printf("3つの整数の最小値は:%d", number2);
	}

	return 0;
}