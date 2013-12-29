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

HashMap createHash(HashcodeGenerator *getHashCode, KeyComparator *areEqual, int capacity){
    HashMap hash;
    int i = 0;
    hash.bucket = create_array(capacity);
    hash.areEqual = areEqual;
    hash.getHashCode = getHashCode;
    hash.keyList = (DoubleList*)create();
    while(i < hash.bucket.capacity){
        add(&hash.bucket, createSlot());
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
    DoubleList *list = slot->elements;
    return list;
};


Matched_Data checkEachElement(DoubleList* list, KeyComparator* areEqual, void* key){
    Matched_Data result = {NULL,-1};
    Iterator it = getIterator(list);
    Hash_Element *currentElement;
    while(it.hasNext(&it)){
        currentElement = it.next(&it);
        if(areEqual(currentElement->key, key)){
            result.data = currentElement->data;
            result.index = it.position - 1;
        }
    }
    return result;
}

Matched_Data doesKeyMatch(HashMap hash, void* key){
    DoubleList* list = getSlotList(hash, key);
    return checkEachElement(list, hash.areEqual, key);
}

void rehashIfNeeded(HashMap* hash){
    Iterator itArray = getIteratorArray(&hash->bucket);
    Slot* slot;
    while(itArray.hasNext(&itArray)){
        slot = (Slot*)itArray.next(&itArray);
        if(slot->elements->length > 3){
            rehash(hash);
            return;            
        }
    }
}

int put(HashMap *hash, void *key, void *value){
    Matched_Data dataFound = doesKeyMatch(*hash, key);
    DoubleList* list;
    Hash_Element *elementToInsert;
    if(dataFound.index > -1)
        HashMap_remove(hash, key);
    list = getSlotList(*hash, key);
    elementToInsert = createHashElement(key, value);
    insert(list, list->length, elementToInsert);
    rehashIfNeeded(hash);
    return 1;
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

void collectAllKeys(HashMap* hash, DoubleList* keysList){
    Iterator itArrayList = getIteratorArray(&hash->bucket);
    Slot* slot;
    Iterator itLinkList;
    while(itArrayList.hasNext(&itArrayList)){
        slot = itArrayList.next(&itArrayList);
        itLinkList = getIterator(slot->elements);
        while(itLinkList.hasNext(&itLinkList)){
            insert(keysList, keysList->length, itLinkList.next(&itLinkList));
        }
    }
}

Iterator getAllKeys(HashMap hash){
    Iterator hashIterator;
    DoubleList* keysList = hash.keyList;
    dispose(keysList);
    keysList = create();
    collectAllKeys(&hash, keysList);
    hashIterator = getIterator(keysList);
    hashIterator.next = &getNextKey;
    return hashIterator;
}

void resetHash(HashMap* hash, DoubleList* keyList){
    Iterator itList = getIterator(keyList);
    Hash_Element* element;
    while(itList.hasNext(&itList)){
        element = itList.next(&itList);
        HashMap_remove(hash, element->key);
    }
}

void increaseBucket(HashMap* hash){
    int i = 0;
    int capacity = hash->bucket.capacity;
    while(i < capacity){
        add(&hash->bucket, createSlot());
        i++;
    }
}

void reInsertEachElement(HashMap* hash, DoubleList* keysList){
    Iterator itList = getIterator(keysList);
    Hash_Element* element;
    while(itList.hasNext(&itList)){
        element = itList.next(&itList);
        put(hash, element->key, element->data);
    }
}

void rehash(HashMap* hash){
    DoubleList *keysList = create();
    collectAllKeys(hash, keysList);
    resetHash(hash, keysList);
    increaseBucket(hash);
    reInsertEachElement(hash, keysList);
    dispose(keysList);
}