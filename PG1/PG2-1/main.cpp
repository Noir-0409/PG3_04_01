#include <stdio.h>

int main()
{
	

	
	char moji;
	printf("入力する文字:");
	moji = getchar();
	printf("入力した文字:%c\n", moji);

	int num;
	
	printf("入力する数字:");
	scanf_s("%d", &num);
	printf("入力した数字:%d", num);
	return 0;
}