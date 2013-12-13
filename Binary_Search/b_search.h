#include <stdlib.h>

typedef const void* constVoidPtr;
typedef int CompareFunc (constVoidPtr ,constVoidPtr);
void* binarySearch (constVoidPtr key, constVoidPtr base,
               size_t totalElements, size_t elementSize,
               CompareFunc* compare);

void sortElements(void* pBase, size_t totalElements,
				 size_t elementSize, CompareFunc* compare);