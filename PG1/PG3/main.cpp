#include <stdio.h>
int main() {
	int number = 0;

	scanf_s("%d", &number);

	if (number > 50) {
		printf("入力した値は50より大きい", number);
	}

	else if (number < 50) {
		printf("入力した値は50より小さい",number);

	}

	else  {
		printf("入力した値は50", number);
	}
	return 0;
}