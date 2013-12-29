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
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	ASSERT(put(&hash, &key1, &prateek));
	ASSERT(&prateek == HashMap_getData(hash, &key1));
}

void test_inserts_multiple_data_in_hash_map(){
	Intern prateek = {12,"Prateek"};
	int key1 = 12;
	Intern shweta = {15, "shweta"};
	int key2 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	ASSERT(put(&hash, &key1, &prateek));
	ASSERT(&prateek == HashMap_getData(hash, &key1));
	ASSERT(put(&hash, &key2, &shweta));
	ASSERT(&shweta == HashMap_getData(hash, &key2));
}

void test_inserts_key_as_alphabet(){
	Word rich = {"Rich","Wealthy","Poor"};
	String key = "Rich";
	HashMap hash = createHash(getAsciiTotal, areWordsEqual, 10);
	ASSERT(put(&hash, &key, &rich));
	ASSERT(&rich == HashMap_getData(hash, &key));
}

void test_gives_the_data_with_matched_the_given_Key(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	ASSERT(put(&hash, &key1, &shweta));
	ASSERT(&shweta == HashMap_getData(hash, &key1));
}

void test_gives_NULL_when_key_is_not_present(){
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	ASSERT(NULL == HashMap_getData(hash, &key1));
}

void test_deletes_the_value_matched_to_given_key(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	ASSERT(put(&hash, &key1, &shweta));
	ASSERT(HashMap_remove(&hash, &key1));
	ASSERT(NULL == HashMap_getData(hash, &key1));	
}

void test_deletion_failed_when_key_is_not_present(){
	int key1 = 15;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	ASSERT(0 == HashMap_remove(&hash, &key1));
	ASSERT(NULL == HashMap_getData(hash, &key1));	
}

void test_deletion_of_an_element_having_key_as_alphabet(){
	Word rich = {"Rich","Wealthy","Poor"};
	String key = "Rich";
	HashMap hash = createHash(getAsciiTotal, areWordsEqual, 10);
	ASSERT(put(&hash, &key, &rich));
	ASSERT(HashMap_remove(&hash, &key));
	ASSERT(NULL == HashMap_getData(hash, &key));
}

void test_gives_iterator_that_tells_the_next_key_is_present_or_not(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	Iterator it;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	put(&hash, &key1, &shweta);
	it = getAllKeys(hash);
	ASSERT(1 == it.hasNext(&it));
}

void test_iterator_gives_the_key_of_next_element(){
	Intern shweta = {15, "shweta"};
	int key1 = 15;
	Iterator it;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	put(&hash, &key1, &shweta);
	it = getAllKeys(hash);
	ASSERT(&key1 == it.next(&it));
}

void test_iterotar_gives_null_when_the_next_data_is_not_present(){
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	Iterator it = getAllKeys(hash);
	ASSERT(NULL == it.next(&it));
	ASSERT(NULL == it.next(&it));
	ASSERT(0 == it.hasNext(&it));
}

void test_iterator_gives_the_itearator_to_get_all_keys_of_hash(){
	Intern interns[5] = {{14, "Prateek"},{15,"Manish"},{18,"Uday"},{20,"Manali"},{12,"Raaz"}};
	int keys[5] = {14,15,18,20,12};
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	Iterator it;
	put(&hash, &keys[0], &interns[0]);
	put(&hash, &keys[1], &interns[1]);
	put(&hash, &keys[2], &interns[2]);
	put(&hash, &keys[3], &interns[3]);
	put(&hash, &keys[4], &interns[4]);
	it = getAllKeys(hash);
	ASSERT(&keys[3] == it.next(&it));
	ASSERT(&keys[4] == it.next(&it));
	ASSERT(&keys[0] == it.next(&it));
	ASSERT(&keys[1] == it.next(&it));
	ASSERT(&keys[2] == it.next(&it));
}

void test_updates_the_value_of_key_if_is_already_present(){
	Intern shweta = {15, "shweta"};
	Intern shwetha = {15, "shwetha"};
	int key1 = 15;
	Iterator it;
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	put(&hash, &key1, &shweta);
	ASSERT(&shweta == HashMap_getData(hash, &key1));
	put(&hash, &key1, &shwetha);
	ASSERT(&shwetha == HashMap_getData(hash, &key1));
	it = getAllKeys(hash);
	ASSERT(&key1 == it.next(&it));
	ASSERT(0 == it.hasNext(&it));
}

void test_hash_map_rearranged_after_a_limit(){
	Intern interns[3] = {{4, "Prateek"},{19,"Manali"},{12,"Raaz"}};
	int keys[3] = {4,19,12};
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 10);
	Iterator it;
	put(&hash, &keys[0], &interns[0]);
	put(&hash, &keys[1], &interns[1]);
	put(&hash, &keys[2], &interns[2]);
	it = getAllKeys(hash);
	ASSERT(&keys[2] == it.next(&it));
	ASSERT(&keys[0] == it.next(&it));
	ASSERT(&keys[1] == it.next(&it));
	rehash(&hash);
	it = getAllKeys(hash);
	ASSERT(&keys[0] == it.next(&it));
	ASSERT(&keys[2] == it.next(&it));
	ASSERT(&keys[1] == it.next(&it));
}

void test_perform_rehashing_if_needed(){
	Intern interns[4] = {{4, "Prateek"},{18,"Manali"},{12,"Raaz"},{10,"Digs"}};
	int keys[4] = {4,18,12,10};
	HashMap hash = createHash(getKeyAsCode, areInternsKeyEqual, 2);
	Iterator it;
	put(&hash, &keys[0], &interns[0]);
	put(&hash, &keys[1], &interns[1]);
	put(&hash, &keys[2], &interns[2]);
	it = getAllKeys(hash);
	ASSERT(&keys[0] == it.next(&it));
	ASSERT(&keys[1] == it.next(&it));
	ASSERT(&keys[2] == it.next(&it));
	put(&hash, &keys[3], &interns[3]);
	it = getAllKeys(hash);
	ASSERT(&keys[0] == it.next(&it));
	ASSERT(&keys[2] == it.next(&it));
	ASSERT(&keys[1] == it.next(&it));
	ASSERT(&keys[3] == it.next(&it));
}