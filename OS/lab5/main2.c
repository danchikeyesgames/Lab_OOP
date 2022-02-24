#include "lib1.h"           // подгружаются две динамические библиотеки во время исполнения
#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    int k, A, B, num;
    float a, b;
    void* library;
    int current = 0;
    char libs[2][8] = {"lib1.so", "lib2.so"};
    int (*FirstFunc) (int A, int B);
    float (*SecondFunc) (float A, float B);

    library = dlopen(libs[current], RTLD_LAZY);
    if (!library) {
        printf("error -> %s\n", dlerror());
        return -1;
    }
    FirstFunc = dlsym(library, "PrimeCount");
    SecondFunc = dlsym(library, "Square");

    while (scanf("%d", &num) > 0) {
        switch(num) {
            case 0:
                dlclose(library);
                current++;
                library = dlopen(libs[current %= 2], RTLD_LAZY);
                FirstFunc = dlsym(library, "PrimeCount");
                SecondFunc = dlsym(library, "Square");
                break;
            case 1:
                scanf("%d %d", &A, &B);
                printf ("your count prime num: %d \n", FirstFunc(A, B));
                break;
            case 2:
                scanf("%f %f", &a, &b);
                printf("Your Square: %.2f \n", SecondFunc(a, b));
                break;
            default:
                printf("incorrected format\n");
        }
    }

    dlclose(library);
    return 0;
}