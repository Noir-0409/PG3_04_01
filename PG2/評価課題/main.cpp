#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cell {
    char str[32];
    struct Cell* next;
};

void create(Cell *endCell, const char* buf) {
    Cell* newCell;

    newCell = (Cell*)malloc(sizeof(Cell));

    strcpy_s(newCell->str, 32, buf);
    newCell->next = NULL;

    while (endCell->next != NULL) {
        endCell = endCell->next;
    }
    endCell->next = newCell;
}

void index(Cell *endCell) {
    while (endCell->next != NULL) {
        endCell = endCell->next;
        printf("%s\n", endCell->str);
    }
}
int main() {
    Cell head;
    head.next = nullptr;
    char str[32];

    while (1) {
        printf("D‚«‚È‚¨õi‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
        scanf_s("%s", str, 32);
        create(&head, str);

        index(&head);
    }
    return 0;

}//•Â‚¶‚é