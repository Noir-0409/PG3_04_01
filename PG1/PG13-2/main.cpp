#include<stdio.h>


void swap(int* x, int* y) {
    int temp;

    temp = *x;
    x = y;
    *y = temp;
}


void insertion_sort(int array[], int array_size) {
    int i, j;

    for (i = 1; i < array_size; i++) {
        j = i;
        while ((j > 0) && (array[j - 1] > array[j])) {
            swap(&array[j - 1], &array[j]);
            j--;
        }
    }
}

int main() {
    int array[10] = { 2, 1, 8, 5, 4, 7, 9, 0, 6, 3 };
    int i;

    printf("挿入ソート前: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    insertion_sort(array, 10);

    printf("挿入ソート後: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}