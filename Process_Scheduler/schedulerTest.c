#include <string.h>
#include <stdlib.h>
#include "testUtils.h"
#include "scheduler.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

PScheduler* scheduler;

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
	Queue_element* element;
	scheduler = createScheduler();
	addProcess(scheduler, process1);
	addProcess(scheduler, process2);
	element = (Queue_element*)scheduler->head->data;
	ASSERT(areProcessEqual(*process2, *(Process*)element->data));
	element = (Queue_element*)scheduler->head->next->data;
	ASSERT(areProcessEqual(*process1, *(Process*)element->data));
}

void test_adds_three_new_process_into_Scheduler_according_to_their_priority(){
	Process* process1 = generateProcess("Mozila", 50, 5);
	Process* process2 = generateProcess("chrome", 100, 3);
	Process* process3 = generateProcess("Task", 100, 4);
	Queue_element* element;
	scheduler = createScheduler();
	addProcess(scheduler, process1);
	addProcess(scheduler, process2);
	addProcess(scheduler, process3);
	element = (Queue_element*)scheduler->head->data;
	ASSERT(areProcessEqual(*process2, *(Process*)element->data));
	element = (Queue_element*)scheduler->head->next->data;
	ASSERT(areProcessEqual(*process3, *(Process*)element->data));
	element = (Queue_element*)scheduler->head->next->next->data;
	ASSERT(areProcessEqual(*process1, *(Process*)element->data));
	scheduler = createScheduler();
}

void test_executes_processes_of_available_in_scheduler(){
	Process* process1 = generateProcess("Mozila", 50, 5);
	Process* expected1 = generateProcess("Mozila", 0, 5);
	Process* process2 = generateProcess("chrome", 100, 3);
	Process* expected2 = generateProcess("chrome", 0, 3);
	Process* process3 = generateProcess("Task", 100, 4);
	Process* expected3 = generateProcess("Task", 0, 4);
	Queue_element* element;
	scheduler = createScheduler();
	addProcess(scheduler, process1);
	addProcess(scheduler, process2);
	addProcess(scheduler, process3);
	executeProcess(scheduler, 10);
	element = (Queue_element*)scheduler->head->data;
	ASSERT(areProcessEqual(*expected2, *(Process*)element->data));
	element = (Queue_element*)scheduler->head->next->data;
	ASSERT(areProcessEqual(*expected3, *(Process*)element->data));
	element = (Queue_element*)scheduler->head->next->next->data;
	ASSERT(areProcessEqual(*expected1, *(Process*)element->data));
	free(expected1);
	free(expected2);
	free(expected3);
	printf("Mai yah\n");
}
