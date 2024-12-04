#include <stdio.h>

int main() {

	int matrix4a[4][4]{
		{0,0,0,0},
		{1,1,1,1},
		{2,2,2,2},
		{3,3,3,3}
	};

	int matrix4b[4][4]{
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3}
	};

	printf("二次元配列a\n");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d,", matrix4a[i][j]);
		}
		printf("\n");
	}

	

	printf("二次元配列b\n");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d,", matrix4b[i][j]);
		}
		printf("\n");
	}

	
	printf("二次元配列a+二次元配列b\n");

	for (int i=0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			
			
			printf("%d,", matrix4a[i][j] + matrix4b[i][j]);
		}
		printf("\n");
	}
		
	
	return 0;

}