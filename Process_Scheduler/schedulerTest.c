#include <string.h>
#include <stdlib.h>
#include "testUtils.h"
#include "scheduler.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

DLList* scheduler;

void tearDown(){
	dispose(scheduler);
}

int areProcessEqual(Process expected, Process actual){
	int res = expected.runTime == actual.runTime && expected.priority == actual.priority;
	if(!res) return res;
	return 0 == strcmp(expected.name, actual.name);
}

void test_creates_a_process_scheduler(){
	scheduler = createScheduler();
	ASSERT(0x0 == scheduler->head);
	ASSERT(0 == scheduler->length);
}

void test_generates_a_new_process_for_scheduler(){
	Process* process = generateProcess("Mozila", 10 , 1);
	Process expected = {"Mozila",10,1};
	scheduler =  createScheduler();
	ASSERT(areProcessEqual(expected, *process));
	free(process);
}

void test_adds_a_new_process_into_Scheduler(){
	Process* process = generateProcess("Mozila", 10, 1);
	int result;
	Queue_element* element;
	scheduler = createScheduler();
	result = addProcess(scheduler, process);
	ASSERT(1 == result);
	element = (Queue_element*)scheduler->head->data;
	ASSERT(areProcessEqual(*process, *(Process*)element->data));
}

void test_adds_a_new_process_into_Scheduler_according_to_its_priority(){
	Process* process1 = generateProcess("Mozila", 50, 2);
	Process* process2 = generateProcess("chrome", 100, 1);
	int result;
	Queue_element* element;
	scheduler = createScheduler();
	result = addProcess(scheduler, process1);
	ASSERT(1 == result);
	result = addProcess(scheduler, process2);
	ASSERT(1 == result);
	element = (Queue_element*)scheduler->head->data;
	ASSERT(areProcessEqual(*process2, *(Process*)element->data));
	element = (Queue_element*)scheduler->head->next->data;
	ASSERT(areProcessEqual(*process1, *(Process*)element->data));
}
