#include <Stdio.h>

int clamp(int num, int min, int max) {

	if (num > max) {

		return max;

	} else if (num < min) {

		return min;

	} else {

		return num;

	}

}

	int main() {

		for (int i = 0; i < 3; i++) {

			int min = 0;

			int max = 0;

			int num = 0;

			int a = 0;

			printf("�ŏ��l(min)����͂��ĉ������F");

			scanf_s("%d", &min);

			printf("�ő�l(max)����͂��ĉ������F");

			scanf_s("%d", &max);

			printf("min~max�͈̔͂Ő���������num�̒l����͂��ĉ������F");

			scanf_s("%d", &num);

			a = clamp(num, min, max);

			printf("�l�𐧌��������ʁF%d\n", a);

		}

		return 0;

}