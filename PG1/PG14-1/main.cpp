#include <Stdio.h>

	int sum(int a, int b) {
		if (a < b) {
			return a;
		}
	}

	int main(){

		int num = -100;
		
		int num2 = 200;

		int z = sum(num, num2);

		printf("num�ɑ������l����́F%d\n", num);

		printf("num2�ɑ������l����́F%d\n", num2);

		printf("num��num2��Min�֐����g���Ēl���Ⴂ����\������F%d",z);


	return 0;
}