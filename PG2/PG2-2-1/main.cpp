#include <stdio.h>

int main() {

	int state = 0b1010;

	int a = 0b1000; // ����

	int b = 0b0100; // �Ή�

	int c = 0b0010; // ��

	int d = 0b0001; // �퓬�s�\

	printf("state=%d\n", state);

	if (state & a) {

		printf("����\n");

	}

	if (state & b) {

		printf("�Ή�\n");

	}

	if (state & c) {

		printf("��\n");

	}

	if (state & d) {

		printf("�퓬�s�\\n");
	}

	

	return 0;

}