#include <stdlib.h>
#include <string.h>
#include "hashMap.h"
#include "testUtils.h"
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

typedef struct{
	int empId;
	char* name;
}Intern;

typedef struct{
	String word;
	String synanom;
	String antynom;
}Word;

int areInternsKeyEqual(void* first, void* second){
	return *(int*)first == *(int*)second;
}

int areWordsEqual(void* first, void* second){
	return 0 == strcmp((char*)first, (char*)second);
}

int getAsciiTotal(void* key){
	int i,total = 0;
	char* data = (char*)key;
	for (i = 0; i < strlen(data); ++i){
		total += data[i];
	}
	return total;
}


int getKeyAsCode(void* key){
	return *(int*)key;
}

void test_inserts_first_data_in_hash_map(){
	Intern prateek = {12,"Prateek"};
	int key1 = 12;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	ASSERT(put(&hash, &key1, &prateek));
	ASSERT(&prateek == HashMap_getData(hash, &key1));
}

void test_inserts_multiple_data_in_hash_map(){
	Intern prateek = {12,"Prateek"};
	int key1 = 12;
	Intern shweta = {15, "shweta"};
	int key2 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	ASSERT(put(&hash, &key1, &prateek));
	ASSERT(&prateek == HashMap_getData(hash, &key1));
	ASSERT(put(&hash, &key2, &shweta));
	ASSERT(&shweta == HashMap_getData(hash, &key2));
}

void test_inserts_key_as_alphabet(){
	Word rich = {"Rich","Wealthy","Poor"};
	String key = "Rich";
	HashMap hash = createHash(getAsciiTotal, areWordsEqual);
	ASSERT(put(&hash, &key, &rich));
	ASSERT(&rich == HashMap_getData(hash, &key));
}

void test_gives_the_data_with_matched_the_given_Key(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	ASSERT(put(&hash, &key1, &shweta));
	ASSERT(&shweta == HashMap_getData(hash, &key1));
}

void test_gives_NULL_when_key_is_not_present(){
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	ASSERT(NULL == HashMap_getData(hash, &key1));
}

void test_deletes_the_value_matched_to_given_key(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	ASSERT(put(&hash, &key1, &shweta));
	ASSERT(HashMap_remove(&hash, &key1));
	ASSERT(NULL == HashMap_getData(hash, &key1));	
}

void test_deletion_failed_when_key_is_not_present(){
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	ASSERT(0 == HashMap_remove(&hash, &key1));
	ASSERT(NULL == HashMap_getData(hash, &key1));	
}

void test_deletion_of_an_element_having_key_as_alphabet(){
	Word rich = {"Rich","Wealthy","Poor"};
	String key = "Rich";
	HashMap hash = createHash(getAsciiTotal, areWordsEqual);
	ASSERT(put(&hash, &key, &rich));
	ASSERT(HashMap_remove(&hash, &key));
	ASSERT(NULL == HashMap_getData(hash, &key));
}

void test_gives_iterator_that_tells_the_next_key_is_present_or_not(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	Iterator it;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	put(&hash, &key1, &shweta);
	it = getAllKeys(hash);
	ASSERT(1 == it.hasNext(&it));
}

void test_provides_an_itesrator_of_all_keys_present_in_Hash(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	Iterator it;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual);
	put(&hash, &key1, &shweta);
	it = getAllKeys(hash);
	ASSERT(&key1 == it.next(&it));
	ASSERT(NULL == it.next(&it));
}