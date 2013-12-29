#include <stdlib.h>
typedef int (*compare)(void* first, void* second);

void isort(void* base, size_t numberOfElements, size_t elementSize,
			compare comp); 