#include<stdio.h>

int main() {

	int nums[10] = { 10,20,30,90,80,70,60,55,45,0 };

	printf("éŒ¾‚Ì‘ã“ü‚É‚æ‚é‰Šú‰»\n");

	printf("nums[0]=%d\n", nums[0]);

	printf("nums[5]=%d\n", nums[5]);

	printf("nums[9]=%d\n", nums[9]);

	nums[6] = 1000;

	printf("“Y‚¦š‚Å“Á’è‚Ì—v‘f‚ğw’è‚µ‚Ä‰Šú‰»\n");

	printf("nums[6]=%d\n", nums[6]);

	printf("for‚É‚æ‚é‰Šú‰»\n");

	int i = 0;

	for (int j = 0; j < 5; j++) {

		printf("nums[%d]=%d\n", j, i);
	}

}