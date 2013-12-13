#include "scheduler.h"
#include <stdlib.h>
#include <string.h>

Process* createProcess(char* name,int runTime,int priority){
        Process* process = malloc(sizeof(Process));
        strcpy(process->name, name);
        process->next = NULL;
        process->priority = priority;
        process->runTime = runTime;
        return process;
}

Scheduler* createScheduler(){
        Scheduler *list = calloc(sizeof(Scheduler),1);
        return list;
}
int addBegining(Scheduler *list, Process *process){
        process->next = list->head;
        list->head = process;
        return ++list->length;        
}
int addProcess(Scheduler *list, Process *process){
        Process *previous,*next,*head;
        head = list->head;
        if(list->length == 0)                
                return addBegining(list, process);
        if(process->priority < head->priority)
                return addBegining(list, process);
        while(head->next != NULL){
                previous = head;
                next = head->next;
                if(process->priority < next->priority){
                        previous->next = process;
                        process->next = next;
                        return ++list->length;
                }
                head = head->next;
        }
        head->next = process;
        process->next = NULL;
        return ++list->length;
}
void dispose(Scheduler *list){
        free(list);
}