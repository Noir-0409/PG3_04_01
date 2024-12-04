#include <stdio.h>
int main() {

    int test[10] = { 3,10,4,5,6,1,8,7,9,2 };
    printf_s("選択ソート前\nnumber = ");

    for (int i = 0; i < 10; ++i) {

        printf("%d,", test[i]);

    }
    printf("\n");
    int number = sizeof(test) / sizeof(int);


    int index = 0;

    int work;


    for (int i = 0; i < number; ++i) {

        index = i;



        for (int s = i + 1; s < number; ++s) {

            if (test[s] < test[index]) {


                index = s;

            }

        }

        work = test[i];

        test[i] = test[index];

        test[index] = work;

    }
    printf_s("選択ソート後\nnumber = ");
    for (int i = 0; i < number; ++i) {

        printf("%d,", test[i]);

    }

    return 0;



}