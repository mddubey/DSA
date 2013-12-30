#include "merge-sort.h"

void merge(void **destination,  void** leftBase, void** rightBase, size_t leftLength,
			 size_t rightLength, Comparator* cmp){
	int i = 0,j = 0,k = 0;
	for(; i < leftLength && j < rightLength;){
		if(cmp(leftBase[i], rightBase[j])){
			destination[k] = leftBase[i];
			i++;
		}
		else{
			destination[k] = rightBase[j];
			j++;
		}
		k++;
	}
	while(i < leftLength){
		destination[k] = leftBase[i];
		i++;k++;
	}
	while(j < rightLength){
		destination[k] = rightBase[i];
		j++;k++;
	}
}

void mergeSort(void** base, size_t noOfElements, Comparator* comp){
	int mid = noOfElements/2;
	int leftLength = mid;
	int i;
	int rightLength = noOfElements - mid;
	void** leftBase = calloc(leftLength, sizeof(void*));
	void** rightBase = calloc(rightLength, sizeof(void*));
	if(noOfElements <= 1) return;
	for(i = 0; i < leftLength ;i++){
		leftBase[i] = base[i];
	}
	for(i = mid; i < noOfElements ;i++){
		rightBase[i-mid] = base[i];
	}
	mergeSort(leftBase, leftLength, comp);
	mergeSort(rightBase, rightLength, comp);
	merge(base, leftBase, rightBase, leftLength, rightLength, comp);
	free(leftBase);
	free(rightBase);
}