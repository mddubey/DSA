#include "b_search.h"
#include <memory.h>

void sortElements(void* base, size_t totalElements, size_t elementSize, CompareFunc *compare){
	int i,j,result;
	void *temp = malloc(elementSize);

	for(i = 0;i<totalElements;i++){
		for(j = 0;j<totalElements-i-1;j++){
			result = compare((base + j*elementSize),(base + (j+1)*elementSize));
			if(result > 0){
				memcpy(temp, (base + j*elementSize), elementSize);
				memcpy((base + j*elementSize), (base + (j+1)*elementSize), elementSize);
				memcpy((base + (j+1)*elementSize), temp, elementSize);
			}
		}
	}
	free(temp);
}

void* binarySearch(constVoidPtr key, constVoidPtr base, size_t totalElements, size_t elementSize, CompareFunc *compare){
	int start = 0;
	int end = totalElements - 1;
	int i,result;
	int mid;
	while(start<=end){
		mid = (start + end)/2;
		result = compare(key, base + mid * elementSize);
		if(!result)
			return (void*)(base + mid * elementSize);
		if(result < 0)
			end = mid-1;
		else
			start = mid + 1;
	}
	return NULL;
}
