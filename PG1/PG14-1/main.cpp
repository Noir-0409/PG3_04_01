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

		printf("numに代入する値を入力：%d\n", num);

		printf("num2に代入する値を入力：%d\n", num2);

		printf("numとnum2をMin関数を使って値が低い方を表示する：%d",z);


	return 0;
}