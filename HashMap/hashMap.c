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

typedef struct {
	void* data;
	int index;
}Matched_Data;

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
		insertInArray(&hash.bucket, hash.bucket.length, createSlot());
		i++;
	}
	return hash;
}

int getSlotIndex(int key_val, int capacity){
	return key_val % capacity;
}

DoubleList* getSlotList(HashMap hash, void* key){
	int key_value = hash.getHashCode(key);
	int bucket_index = getSlotIndex(key_value, hash.bucket.capacity);
	Slot* slot = hash.bucket.base[bucket_index];
	DoubleList *list = &slot->elements;
	return list;
};

int put(HashMap *hash, void *key, void *value){
	DoubleList* list = getSlotList(*hash, key);
	Hash_Element *elementToInsert = createHashElement(key, value);
	return insert(list, list->length, elementToInsert);
}

Matched_Data doesKeyMatch(HashMap hash, void* key){
	Matched_Data result = {NULL,-1};
	DoubleList* list = getSlotList(hash, key);
	Iterator it = getIterator(list);
	Hash_Element *currentElement = NULL;
	while(it.hasNext(&it)){
		currentElement = it.next(&it);
		if(hash.areEqual(currentElement->key, key)){
			result.data = currentElement->data;
			result.index = it.position - 1;
		}
	}
	return result;
}

void* HashMap_getData(HashMap hash, void* key){
	Matched_Data elementFound = doesKeyMatch(hash, key);
	return elementFound.data;
}

int HashMap_remove(HashMap* hash, void* key){
	Matched_Data elementFound = doesKeyMatch(*hash, key);
	DoubleList *list = getSlotList(*hash, key);
	return delete_node(list, elementFound.index);
};

void* getNextKey(Iterator *it){
	Iterator hashIterator = getIterator(it->list);
	Hash_Element* element;
	hashIterator.position = it->position;
	element = hashIterator.next(&hashIterator);\
	it->position++;
	if(!element) return NULL;
	return element->key;
}

Iterator getAllKeys(HashMap hash){
	Iterator itArrayList = getIteratorArray(&hash.bucket);
	Slot* slot;
	Iterator itLinkList;
	Iterator hashIterator;
	DoubleList keysList = create();
	while(itArrayList.hasNext(&itArrayList)){
		slot = itArrayList.next(&itArrayList);
		itLinkList = getIterator(&slot->elements);
		while(itLinkList.hasNext(&itLinkList)){
			insert(&keysList, keysList.length, itLinkList.next(&itLinkList));
		}
	}
	hashIterator = getIterator(&keysList);
	hashIterator.next = &getNextKey;
	return hashIterator;
}
