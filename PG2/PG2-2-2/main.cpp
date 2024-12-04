#include <stdio.h>

int main() {

	int* pa;

	int* pb;

	int a = 5;

	int b = 0;

	pa = &a;

	pb = &b;

	printf("%d\n", a);

	printf("%d\n", b);

	printf("%p\n", &pa);

	printf("%p\n", &pb);

	pa = pb;

	printf("%d\n", *pa);

	printf("%d\n", *pb);

	printf("%p\n", pa);

	printf("%p\n", pb);

	pb = &a;

	printf("%d\n", a);

	printf("%d\n", b);

	printf("%p\n", &pa);

	printf("%p\n", &pb);

	return 0;

}