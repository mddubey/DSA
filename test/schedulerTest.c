#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "testUtils.h"
#include "scheduler.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

DLList* process_list;

void tearDown(){
	free(process_list);
}

int areProcessesEqual(Process expected,Process actual){
	int res = expected.priority == actual.priority && expected.runTime == actual.runTime;
	if(!res) return res;
	return 0 == strcmp(expected.name, actual.name);
} 
void test_adds_a_process_to_the_process_list(){
	Process* newProcess = malloc(sizeof(Process));
	strcpy(newProcess->name, "chrome");
	newProcess->priority = 1;newProcess->runTime = 20;
	process_list = create();
	addProcess(process_list, newProcess);
	ASSERT(areProcessesEqual(*newProcess, *(Process*)process_list->head->data));
	ASSERT(1 == process_list->length);
}

void test_adds_a_high_priority_process_first_in_the_list(){
	Process* processes = malloc(sizeof(Process)*2);
	Node* result;
	strcpy(processes[0].name, "chrome");
	processes[0].priority = 2;processes[0].runTime = 40;
	strcpy(processes[1].name, "mozila");
	processes[1].priority = 1;processes[1].runTime = 20;
	process_list = create();
	addProcess(process_list, &processes[0]);
	ASSERT(areProcessesEqual(processes[0], *(Process*)process_list->head->data));
	ASSERT(1 == process_list->length);
	addProcess(process_list, &processes[1]);
	ASSERT(areProcessesEqual(processes[1], *(Process*)process_list->head->data));
	ASSERT(areProcessesEqual(processes[0], *(Process*)process_list->head->next->data));
	ASSERT(2 == process_list->length);
};
