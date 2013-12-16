#include <stdlib.h>
#include <memory.h>
#include "isort.h"

void isort(void** base, size_t totalElements, size_t elementSize, compare comp) {
    int i, j;
    void** temp = malloc(sizeof(void*));
    void** elementToCompare = malloc(sizeof(void*));
    int result;
    for (i = 1; i < totalElements; i++) {
        *temp = base[i];
        for (j = i - 1; j >= 0; j--) {
            *elementToCompare = base[j];
            result = comp(*temp, *elementToCompare);
            if (result >= 0) {
                break; 
            }
            *(elementToCompare + 1) = *elementToCompare;
        } 
    }
    free(temp);
}