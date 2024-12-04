#include <stdio.h>

int main() {

	int matrix4[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	printf("宣言時の代入による初期化\n");
	
	printf("1行1列から1行4列を表示\n");

	printf("%d,%d,%d,%d\n", matrix4[0][0],matrix4[0][1],matrix4[0][2],matrix4[0][3]);

	printf("2行1列から2行4列を表示\n");

	printf("%d,%d,%d,%d\n", matrix4[1][0], matrix4[1][1], matrix4[1][2], matrix4[1][3]);

	printf("3行1列から3行4列を表示\n");

	printf("%d,%d,%d,%d\n", matrix4[2][0], matrix4[2][1], matrix4[2][2], matrix4[2][3]);

	printf("4行1列から4行4列を表示\n");

	printf("%d,%d,%d,%d\n", matrix4[3][0], matrix4[3][1], matrix4[3][2], matrix4[3][3]);
	
	matrix4[3][0] = 100;

	matrix4[3][1] = 200;

	matrix4[3][2] = 50;

	printf("添え字指定による代入\n");

	printf("4行1列、4行2列、4行3列に代入\n");

	printf("%d,%d,%d", matrix4[3][0], matrix4[3][1], matrix4[3][2]);

}

