#include <stdio.h>

int Power(int a,int b) {

	if ( b <= 1) {

		return(1);

	}

	return (a * Power(a, b - 1));

}

int main() {

	int bottom=0;

	int index=0;

	int result=0;

	result = Power(bottom,index);

	printf("������...");

	scanf_s("%d", &bottom);

	printf("�w�������...");

	scanf_s("%d", &index);

	printf("%d��%d���%d", bottom, index, result);

	return 0;

}