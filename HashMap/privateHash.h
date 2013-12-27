#include "include/dList.h"
#include "hashMap.h"

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

Slot* createSlot();
Hash_Element* createHashElement(void* key, void* dataToInsert);
int getSlotIndex(int key_val, int capacity);
DoubleList* getSlotList(HashMap hash, void* key);
Matched_Data doesKeyMatch(HashMap hash, void* key);