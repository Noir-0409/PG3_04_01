#include <stdio.h>
int main() {
	int number = 0;

	scanf_s("%d", &number);

	if (number > 50) {
		printf("���͂����l��50���傫��", number);
	}

	else if (number < 50) {
		printf("���͂����l��50��菬����",number);

	}

	else  {
		printf("���͂����l��50", number);
	}
	return 0;
}