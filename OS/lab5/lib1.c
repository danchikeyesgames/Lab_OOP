#include "lib1.h"
#include <stdio.h>

int PrimeCount(int A, int B) {
    int k = 0, p = 0;
    
    printf("work lib1\n");

    for (int i = A; i <= B; i++) {
        for (int j = 1; j <= i; j++) {
            if (i % j == 0 && i != j && j != 1) {
                p++;
            }
        }

        if (p == 0)
            k++;
        p = 0;
    }

    return k;
}

float Square(float A, float B) {
    printf("work lib1\n");
    return A * B;
}
