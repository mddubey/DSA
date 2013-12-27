#include <stdlib.h>
#include "hashMap.h"
#include "include/dList.h"

typedef struct{
	DoubleList elements;
}Slot;

typedef struct{
	void* key;
	void* data;
}Hash_Element;

Slot* createSlot(){
	Slot* slot = malloc(sizeof(Slot));
	slot->elements = create();
	return slot;
}

Hash_Element* createHashElement(void* key, void* dataToInsert){
	Hash_Element* element = malloc(sizeof(Hash_Element));
	element->data = dataToInsert;
	element->key = key;
	return element;
}

HashMap createHash(HashcodeGenerator *getHashCode, KeyComparator *areEqual){
	HashMap hash;
	Iterator itArray;int i = 0;
	hash.bucket = create_array(10);
	hash.areEqual = areEqual;
	hash.getHashCode = getHashCode;
	itArray = getIteratorArray(&hash.bucket);
	while(i < hash.bucket.capacity){
		hash.bucket.base[i] = createSlot();
		i++;
	}
	return hash;
}

int getSlotIndex(int key_val, int capacity){
	return key_val % capacity;
}

int put(HashMap *hash, void *key, void *value){
	int key_value = hash->getHashCode(key);
	int bucket_index = getSlotIndex(key_value, hash->bucket.capacity);
	Slot* slot = hash->bucket.base[bucket_index];
	DoubleList *list = &slot->elements;
	Hash_Element *elementToInsert = createHashElement(key, value);
	// printf("%d\n", bucket_index);
	return insert(list, list->length, elementToInsert);
}

void* HashMap_get(HashMap hash, void* key){
	int key_value = hash.getHashCode(key);
	int bucket_index = getSlotIndex(key_value, hash.bucket.capacity);
	Slot* slot = hash.bucket.base[bucket_index];
	DoubleList *list = &slot->elements;
	Iterator it = getIterator(list);
	Hash_Element *currentElement = NULL;
	while(it.hasNext(&it)){
		currentElement = it.next(&it);
		if(hash.areEqual(currentElement->key, key))
			return currentElement->data;
	}
	return NULL;
}
