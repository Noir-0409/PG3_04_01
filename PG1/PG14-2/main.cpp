#include <Stdio.h>

int sum(int a, int b) {

	if (a < b) {
		return b;
	}
}

	int main() {

		int num = 200;

		int num2 = 500;

		int z = sum(num, num2);

		printf("numに代入する値を入力：%d\n", num);

		printf("num2に代入する値を入力：%d\n", num2);

		printf("numとnum2をMax関数を使って値が大きい方を表示する：%d", z);

		return 0;

	}
