#include <stdio.h>
int main() {
	int number = 0;

	printf("宝箱を3つ見つけた、しかし1つ取ると他2つを取れなさそうだ\n");

	printf("どの宝箱を選ぶ？\n");

	printf("小さい宝箱　　  ：0\n");

	printf("中くらいの宝箱　：1\n");

	printf("大きい宝箱　  　：2\n");

	scanf_s("%d", &number);

	enum Treasure {
		SMALL,
		MEDIUM,
		LARGE,
	};

	switch (number) {
	case SMALL:
		printf("小さい宝箱を開けた、足元が崩れ奈落の底に落ちた");
		break;

	case MEDIUM:
		printf("中くらいの宝箱を開けた、なんと金の延べ棒50Kgが入っていた");
		break;

	case LARGE:
		printf("大きい宝箱を開けた、なんとミミックだったあなたはおいしく食べられた");
		break;

	default:
		printf("罠を警戒して宝箱を開けるのをやめた…");
		break; 
	}

	return 0;

	}