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

		printf("num�ɑ������l����́F%d\n", num);

		printf("num2�ɑ������l����́F%d\n", num2);

		printf("num��num2��Max�֐����g���Ēl���傫������\������F%d", z);

		return 0;

	}
