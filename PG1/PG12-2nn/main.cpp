#include <stdio.h>

int main() {

	int arr[100] = {};

	for (int i = 0; i < 100; i++) {

		arr[i] = i + 1;

	}

	int searchVal = 0;

	int low = 0;

	int high=99;

	int mid = 0;

	int a = 0;

	printf("�v�������ׂ���������͂��ĉ������F");

	scanf_s("%d",&searchVal);

	while (low <= high) {

		mid = (low + high) / 2;

		if (arr[mid] == searchVal) {

			printf("�v�������ׂ�������%d\n", mid);

			return 0;

		} 
		

		printf("�v�������ׂ�������%d���傫���Fyes�Ȃ�1�Ano�Ȃ�0����́F", arr[mid]);

		scanf_s("%d", &a);

		if (a == 0) {

			high = mid - 1;

		} else {

			low = mid + 1;

		}
	
	}

	printf("�v�������ׂ������͌�����܂���ł���");

	return 0;

}