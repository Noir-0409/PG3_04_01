#include <stdio.h>

int main() {

	printf("���̃v���O�����ł̓V�t�g4�ŌŒ�\n");

	int num = 10;

	printf("�����̑���F�l��%d\n", num);

	printf("num=%d\n", num);
	
	num = num << 4;

	printf("num�����V�t�g�F%d\n", num);

	printf("num*10=%d\n", num * 10);

	num = num >> 4;

	printf("num���E�V�t�g�F%d\n", num);

	int num2 = 20;
	
	printf("�����̑���F�l��1.23\n");

	printf("1.23*(2��4��)=1.23*16=1.23*16\n");

	printf("�Œ菭�����m�̌v�Z���s���̂�num�����V�t�g����\n");

	num = num << 4;

	num2 = num2 << 4;
	
	printf("num+num2=%d\n", num + num2);

	num = num >> 4;

	num2 = num2 >> 4;

	printf("�E�V�t�g�Ŗ߂��F%d",num+num2);

	return 0;

}