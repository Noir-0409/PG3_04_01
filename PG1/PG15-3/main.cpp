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

			printf("最小値(min)を入力して下さい：");

			scanf_s("%d", &min);

			printf("最大値(max)を入力して下さい：");

			scanf_s("%d", &max);

			printf("min~maxの範囲で制限したいnumの値を入力して下さい：");

			scanf_s("%d", &num);

			a = clamp(num, min, max);

			printf("値を制限した結果：%d\n", a);

		}

		return 0;

}