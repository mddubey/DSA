#include <stdlib.h>
#include "hashMap.h"
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

typedef struct{
	int empId;
	char* name;
}Intern;

int areInternsEqual(void* first, void* second){
	Intern firstIntern = *(Intern*)first;
	Intern secondIntern = *(Intern*)second;
	return firstIntern.empId == secondIntern.empId;
}

int getKey(void* key){
	return *(int*)key;
}

void test_inserts_first_data_in_hash_map(){
	Intern prateek = {12,"Prateek"};
	int key1 = 12;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(put(&hash, &key1, &prateek));
	ASSERT(&prateek == HashMap_get(hash, &key1));
}

void test_inserts_multiple_data_in_hash_map(){
	Intern prateek = {12,"Prateek"};
	int key1 = 12;
	Intern shweta = {15, "shweta"};
	int key2 = 15;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(put(&hash, &key1, &prateek));
	ASSERT(&prateek == HashMap_get(hash, &key1));
	ASSERT(put(&hash, &key2, &shweta));
	ASSERT(&shweta == HashMap_get(hash, &key2));
}

void test_gives_the_data_with_matched_the_given_tree(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(put(&hash, &key1, &shweta));
	ASSERT(&shweta == HashMap_get(hash, &key1));
}

void test_gives_NULL_when_key_is_not_present(){
	int key1 = 15;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(NULL == HashMap_get(hash, &key1));
}

void test_deletes_the_value_matched_to_given_key(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(put(&hash, &key1, &shweta));
	ASSERT(HashMap_remove(&hash, &key1));
	ASSERT(NULL == HashMap_get(hash, &key1));	
}

void test_deletion_failed_when_key_is_not_present(){
	int key1 = 15;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(0 == HashMap_remove(&hash, &key1));
	ASSERT(NULL == HashMap_get(hash, &key1));	
}