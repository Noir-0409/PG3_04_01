#include <stdio.h>
#include <stdlib.h>

void* malloc(size_t size);

typedef struct cell {

	int val;

	struct cell* next;
	
} CELL;

int main() {

	CELL head;

	head.next = nullptr;

	void create(CELL * endCell, int val) {

		CELL* newCell;

		newCell = (CELL*)malloc(sizeof(CELL));

		newCell->val = val;

		newCell->next = NULL;

		while (endCell->next != NULL) {

			endCell = endCell->next;

		}

		endCell- > next = newCell;

	}

	void index(CELL * endCell) {

		while (endCell->next != NULL) {

			endCell = endCell->next;

			printf("%d\n", endCell->val);

		}

	}

	return 0;

	}