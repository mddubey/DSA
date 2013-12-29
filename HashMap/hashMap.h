#include "include/arrayList.h"
#include "../Iterator.h"

typedef int KeyComparator (void* first, void* second);
typedef int HashcodeGenerator(void* key);

typedef struct{
	ArrayList bucket;
	void* keyList;
	KeyComparator* areEqual;
	HashcodeGenerator* getHashCode;
}HashMap;

Iterator getAllKeys(HashMap hash);
HashMap createHash(HashcodeGenerator* getHashCode, KeyComparator* areEqual, int capacity);
int put(HashMap* hash, void* key, void* value);
void rehash(HashMap* hash);
void* HashMap_getData(HashMap hash, void* key);
int HashMap_remove(HashMap* hash, void* key);
void disposeHash(HashMap* hash);