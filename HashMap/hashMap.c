#include <stdlib.h>
#include "privateHash.h"


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
		add(&hash.bucket, createSlot());
		i++;
	}
	return hash;
}

int getSlotIndex(int key_val, int capacity){
	return key_val % capacity;
}

void checkEachElement(DoubleList* list, Matched_Data* result, KeyComparator* areEqual, void* key){
	Iterator it = getIterator(list);
	Hash_Element* currentElement;
	while(it.hasNext(&it)){
		currentElement = it.next(&it);
		if(areEqual(currentElement->key, key)){
			result->data = currentElement->data;
			result->index = it.position - 1;
		}
	}
}

Matched_Data doesKeyMatch(HashMap hash, void* key){
	Matched_Data result = {NULL,-1};
	DoubleList* list = getSlotList(hash, key);
	checkEachElement(list, &result, hash.areEqual, key);
	return result;
}

DoubleList* getSlotList(HashMap hash, void* key){
	int key_value = hash.getHashCode(key);
	int bucket_index = getSlotIndex(key_value, hash.bucket.capacity);
	Slot* slot = hash.bucket.base[bucket_index];
	DoubleList *list = &slot->elements;
	return list;
};

int put(HashMap *hash, void *key, void *value){
	Matched_Data dataFound = doesKeyMatch(*hash, key);
	DoubleList* list;
	Hash_Element *elementToInsert;
	if(dataFound.index > -1)
		HashMap_remove(hash, key);
	list = getSlotList(*hash, key);
	elementToInsert = createHashElement(key, value);
	return insert(list, list->length, elementToInsert);
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
	element = hashIterator.next(&hashIterator);
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
	// collectAllKeys(&hash.bucket, &keysList);
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
