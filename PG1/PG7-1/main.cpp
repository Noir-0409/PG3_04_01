#include<stdio.h>

int main() {

	int nums[10] = { 10,20,30,90,80,70,60,55,45,0 };

	printf("�錾���̑���ɂ�鏉����\n");

	printf("nums[0]=%d\n", nums[0]);

	printf("nums[5]=%d\n", nums[5]);

	printf("nums[9]=%d\n", nums[9]);

	nums[6] = 1000;

	printf("�Y�����œ���̗v�f���w�肵�ď�����\n");

	printf("nums[6]=%d\n", nums[6]);

	printf("for�ɂ�鏉����\n");

	int i = 0;

	for (int j = 0; j < 5; j++) {

		printf("nums[%d]=%d\n", j, i);
	}

}