#include <stdio.h>

int main() {

	int i=0;

	int MAX = 100;

	printf("探したい数字を入力(1から100):55\n");

	printf("探したい数字：55\n");

	for (int i = 0; i < MAX; i++) {
		if (i==55) {
			break;
		}
	}

	printf("見つかった位置：numbers[%d]", i);

	return 0;
}