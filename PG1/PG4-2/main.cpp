#include <stdio.h>
int main() {
	int count = 0;
	while (true) {
		count++;
		printf("%d\n", count);
		if (count >= 10) {
			break;
		}
	}
	printf("繰り返しを終了する");

	return 0;

}