#include <stdlib.h>

typedef int Comparator(void* first, void* second);
void mergeSort(void** base, size_t noOfElements, Comparator* comp);