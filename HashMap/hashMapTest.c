#include "testUtils.h"
#include "hashMap.h"

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
	int key = 12;
	HashMap hash = createHash(getKey, areInternsEqual);
	ASSERT(put(&hash, &key, &prateek));
}
