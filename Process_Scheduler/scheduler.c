#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

PScheduler* createScheduler(){
	PScheduler* newScheduler = create_queue();
	return newScheduler;
}

Process* generateProcess(char *name, int runTime, int priority){
	Process* newProcess = malloc(sizeof(Process));
	strcpy(newProcess->name, name);
	newProcess->runTime = runTime;
	newProcess->priority = priority;
	return newProcess;
}

int addProcess(PScheduler* scheduler, Process* process){
	Queue_element* element = malloc(sizeof(Queue_element));
	element->data = process;
	element->priority = process->priority;
	return enqueue(scheduler, element);
}

void executeProcess(PScheduler* scheduler, int timeSlice){
	int processFinished = 0;
	Node* node;
	Queue_element* queue; 
	Process* currentProcess;
	if(0 == scheduler->length)
		return;
	node = scheduler->head;
	while(processFinished != scheduler->length){
		queue = node->data;
		currentProcess = queue->data;
		if(currentProcess->runTime > 0){
			currentProcess->runTime -= timeSlice;
			if(currentProcess->runTime<=0)
				processFinished++;
			if(node->next == NULL)
				node->next = scheduler->head;
		}		
		node = node->next;
	}
}