#include "lib1.h"
#include <stdio.h>
#include <stdlib.h>

int PrimeCount(int A, int B) {
    int k = 0, p = 0;
    int* nums = (int*) malloc(sizeof(int) * B + 1);

    printf("work lib2\n");

    for (int i = 0; i <= B; i++)
           nums[i] = i;

       
       for (int s = 2; s <= B; s++) {
           if (nums[s] != 0) {
               for(int j = s*2; j <= B; j += s)
                   nums[j] = 0;
           }
       }
       for (int i = A; i <= B; i++)
           if (nums[i] != 0)
                k++;

    free(nums);
    return k;
}

float Square(float A, float B) {
    printf("work lib2\n");
    return A * B / 2;
}