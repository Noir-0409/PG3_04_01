#include <Stdio.h>

int main() {

	int arr[100] = {};

	int searchVall = 0;

	int low[1] = { 1 };

	int high[1] = {-1};

	int mid = 0;

	while (low[0] <= high[0]) {

		mid = (low[0] + high[0]) / 2;

		if (arr[mid] == searchVall) {

			searchVall = mid;

		} else if (arr[mid] > searchVall) {

			high[0] = mid - 1;

		} else if (arr[mid] < searchVall) {

			low[0] = mid + 1;

		}

	}

		printf("�v�������ׂ�����(1����100�܂�)���͂��ĉ�����\n");

		scanf_s("\n");

		printf("�v�������ׂ�������%d���傫���Fyes�Ȃ�1�Ano�Ȃ�O�����\n", mid);

		scanf_s("\n");

	
	

	return 0;

}