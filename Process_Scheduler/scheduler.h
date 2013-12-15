#include "./include/priorityQueue.h"

typedef struct {
	char name[50];
	int runTime;
	int priority;
}Process;

typedef PQueue PScheduler;

PScheduler* createScheduler();
Process* generateProcess(char* name,int runTime,int priority);
int addProcess(PScheduler* scheduler, Process* process);
void executeProcess(PScheduler* scheduler, int timeSlice);