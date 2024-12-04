#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
	unsigned int currentime = time(nullptr);
	srand(currentime);

	int num =0;

	while (num < 10) {

		int randumNomber = rand();

		printf("%d‰ñ–ÚF%d\n", num + 1, randumNomber % 40 - 20);

		num++;
	}
	
	return 0;
}
