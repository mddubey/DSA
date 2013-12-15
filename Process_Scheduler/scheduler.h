#include "./include/priorityQueue.h"

typedef struct {
	char name[50];
	int runTime;
	int priority;
}Process;

DLList* createScheduler();
Process* generateProcess(char* name,int runTime,int priority);
int addProcess(DLList* scheduler, Process* process);
