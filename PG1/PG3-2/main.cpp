#include <stdio.h>
int main() {
	int number = 0;

	printf("�󔠂�3�������A������1���Ƒ�2�����Ȃ�������\n");

	printf("�ǂ̕󔠂�I�ԁH\n");

	printf("�������󔠁@�@  �F0\n");

	printf("�����炢�̕󔠁@�F1\n");

	printf("�傫���󔠁@  �@�F2\n");

	scanf_s("%d", &number);

	enum Treasure {
		SMALL,
		MEDIUM,
		LARGE,
	};

	switch (number) {
	case SMALL:
		printf("�������󔠂��J�����A����������ޗ��̒�ɗ�����");
		break;

	case MEDIUM:
		printf("�����炢�̕󔠂��J�����A�Ȃ�Ƌ��̉��ז_50Kg�������Ă���");
		break;

	case LARGE:
		printf("�傫���󔠂��J�����A�Ȃ�ƃ~�~�b�N���������Ȃ��͂��������H�ׂ�ꂽ");
		break;

	default:
		printf("㩂��x�����ĕ󔠂��J����̂���߂��c");
		break; 
	}

	return 0;

	}