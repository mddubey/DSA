#include <memory.h>
#include "isort.h"

void isort(void** base, size_t numberOfElements, compare comp) {
    int i, j;
    void** temp = malloc(sizeof(void*));
    int comparisonResult;    
    for (i = 1; i < numberOfElements; i++) {
        *temp = base[i];

        for (j = i - 1; j >= 0; j--) {
            comparisonResult = comp(*temp, base[j]);
            if (comparisonResult >= 0) {
                break; 
            }
            base[j + 1] = base[j];
        } 
        base[j+1] = *temp;
    }    
    free(temp);
}
