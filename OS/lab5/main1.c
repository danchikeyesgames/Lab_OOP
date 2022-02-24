#include "lib1.h"           // подгружается динамическая первая библиотека на этапе компиляции
#include <stdio.h>

int main(void) {
    int A, B, num;
    float a, b;

    while (scanf("%d", &num) > 0) {
        switch(num) {
            case 1:
                scanf("%d %d", &A, &B);
                printf ("your count prime num: %d \n", PrimeCount(A, B));
                break;
            case 2:
                scanf("%f %f", &a, &b);
                printf("Your Square: %.2f \n", Square(A, B));
                break;
            default:
                printf("incorrected format\n");
        }
    }

    return 0;
}
