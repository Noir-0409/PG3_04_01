#include <stdio.h>
int main() {
	int number = 0;
	int number2 = 0;
	int number3 = 0;

	printf("3�̐����̍ŏ��l�����߂�\n");
	printf("1�ڂ̒l����͂��Ă�������:");
	scanf_s("%d", &number);
	printf("2�ڂ̒l����͂��Ă�������:");
	scanf_s("%d", &number2);
	printf("3�ڂ̒l����͂��Ă�������:");
	scanf_s("%d", &number3);
	
	if (number > number2) {
		if (number2 > number3)
			printf("3�̐����̍ŏ��l��:%d",number3);
	}
	
	if (number2 > number) {
		if (number > number3)
			printf("3�̐����̍ŏ��l��:%d", number3);
	}
	
	if (number2 > number3) {
		if (number3 > number);
		printf("3�̐����̍ŏ��l��:%d", number);
	}

	if (number3 > number2) {
		if (number2 > number);
		printf("3�̐����̍ŏ��l��:%d", number);
	}

	if (number > number3) {
		if (number3 > number2);
		printf("3�̐����̍ŏ��l��:%d", number2);
	}

	if (number3 > number) {
		if (number > number2);
		printf("3�̐����̍ŏ��l��:%d", number2);
	}

	return 0;
}