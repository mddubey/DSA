#include <stdlib.h>
typedef int (*compare)(void* first, void* second);

void bubbleSort(void** base, size_t numberOfElements, compare comp); 