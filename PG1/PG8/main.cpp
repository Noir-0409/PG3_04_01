#include <stdio.h>

int main() {

	int matrix4[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	printf("�錾���̑���ɂ�鏉����\n");
	
	printf("1�s1�񂩂�1�s4���\��\n");

	printf("%d,%d,%d,%d\n", matrix4[0][0],matrix4[0][1],matrix4[0][2],matrix4[0][3]);

	printf("2�s1�񂩂�2�s4���\��\n");

	printf("%d,%d,%d,%d\n", matrix4[1][0], matrix4[1][1], matrix4[1][2], matrix4[1][3]);

	printf("3�s1�񂩂�3�s4���\��\n");

	printf("%d,%d,%d,%d\n", matrix4[2][0], matrix4[2][1], matrix4[2][2], matrix4[2][3]);

	printf("4�s1�񂩂�4�s4���\��\n");

	printf("%d,%d,%d,%d\n", matrix4[3][0], matrix4[3][1], matrix4[3][2], matrix4[3][3]);
	
	matrix4[3][0] = 100;

	matrix4[3][1] = 200;

	matrix4[3][2] = 50;

	printf("�Y�����w��ɂ����\n");

	printf("4�s1��A4�s2��A4�s3��ɑ��\n");

	printf("%d,%d,%d", matrix4[3][0], matrix4[3][1], matrix4[3][2]);

}

