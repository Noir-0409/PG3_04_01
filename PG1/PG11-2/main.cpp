#include <stdio.h>

int main() {

	printf("このプログラムではシフト4で固定\n");

	int num = 10;

	printf("整数の代入：値は%d\n", num);

	printf("num=%d\n", num);
	
	num = num << 4;

	printf("numを左シフト：%d\n", num);

	printf("num*10=%d\n", num * 10);

	num = num >> 4;

	printf("numを右シフト：%d\n", num);

	int num2 = 20;
	
	printf("少数の代入：値は1.23\n");

	printf("1.23*(2の4乗)=1.23*16=1.23*16\n");

	printf("固定少数同士の計算を行うのでnumを左シフトする\n");

	num = num << 4;

	num2 = num2 << 4;
	
	printf("num+num2=%d\n", num + num2);

	num = num >> 4;

	num2 = num2 >> 4;

	printf("右シフトで戻す：%d",num+num2);

	return 0;

}