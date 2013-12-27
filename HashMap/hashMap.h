#include "include/arrayList.h"
#include "../Iterator.h"

typedef int KeyComparator (void* first, void* second);
typedef int HashcodeGenerator(void* key);

typedef struct{
	ArrayList bucket;
	KeyComparator* areEqual;
	HashcodeGenerator* getHashCode;
}HashMap;

HashMap createHash(HashcodeGenerator* getHashCode, KeyComparator* areEqual);
int put(HashMap* hash, void* key, void* value);
void* HashMap_getData(HashMap hash, void* key);
int HashMap_remove(HashMap* hash, void* key);
Iterator getAllKeys(HashMap hash);