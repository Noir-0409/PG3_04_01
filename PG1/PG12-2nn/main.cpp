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

	printf("思い浮かべた数字を入力して下さい：");

	scanf_s("%d",&searchVal);

	while (low <= high) {

		mid = (low + high) / 2;

		if (arr[mid] == searchVal) {

			printf("思い浮かべた数字は%d\n", mid);

			return 0;

		} 
		

		printf("思い浮かべた数字は%dより大きい：yesなら1、noなら0を入力：", arr[mid]);

		scanf_s("%d", &a);

		if (a == 0) {

			high = mid - 1;

		} else {

			low = mid + 1;

		}
	
	}

	printf("思い浮かべた数字は見つかりませんでした");

	return 0;

}