#include "include/dList.h"
#include "hashMap.h"

typedef struct{
	DoubleList* elements;
}Slot;

typedef struct{
	void* key;
	void* data;
}Hash_Element;

typedef struct {
	void* data;
	int index;
}Matched_Data;

Slot* createSlot();
void rehash(HashMap* hash);
void rehashIfNeeded(HashMap* hash);
void increaseBucket(HashMap* hash);
int getSlotIndex(int key_val, int capacity);
DoubleList* getSlotList(HashMap hash, void* key);
Matched_Data doesKeyMatch(HashMap hash, void* key);
void resetHash(HashMap* hash, DoubleList* keyList);
void collectAllKeys(HashMap* hash, DoubleList* keysList);
void reInsertEachElement(HashMap* hash, DoubleList* keysList);
Hash_Element* createHashElement(void* key, void* dataToInsert);