#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

	printf("�ϐ�str(VisualStudio)�̕�����̒������擾����\n");

	char str[30] = "VisualStudio";

	int len;

	len = strlen(str);

	printf("����=%d\n", len);

	int islower;

	int c;

	printf("�ϐ�str(VisualStudio)�̕�����̐擪���������ɕύX����\n");

	c = getchar();

	printf("�ԊҌ�=%d\n", c);

	return 0;

}