#include <stdio.h>

struct Vector2 {

	float x;

	float y;

};

int main(){

	Vector2 obja{

		100.0f,120.0f
	};

	Vector2 objb{

		50.0f,200.0f

	};

	printf("�錾���̑���Ɋ�鏉����\n");

	printf("obja(x=%f,y=%f)\n", obja.x, obja.y);

	printf("objb(x=%f,y=%f)\n", objb.x, objb.y);

	printf("�����o�ϐ����w�肵�Ă̏�����\n");

	obja.x = 500.0f;

	obja.y = 250.0f;

	objb.x = 50.0f;

	objb.y = 200.0f;

	printf("obja(x=%f,y=%f)\n", obja.x, obja.y);

	printf("objb(x=%f,y=%f)\n", objb.x, objb.y);

	printf("�����o�ϐ����m�̌v�Z\n");

	printf("obja��objb��x���m�Ay���m�̌v�Z\n");

	printf("sumX=%f,sumY=%f\n", obja.x + objb.x, obja.y + objb.y);

	return 0;
}