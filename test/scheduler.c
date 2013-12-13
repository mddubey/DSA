#include "scheduler.h"


void addProcess(DLList *process_list, Process *process){
	int index;
	int currentPriority;
	Process* currentProcess;
	Node* head;
	if(0x0 == process_list->head)
		index = 0;
	else{
		head = process_list->head;
		currentProcess = head->data;
		if(process->priority<currentProcess->priority)
			index = 0;
		else if(process->priority == currentProcess->priority){
			index = 1;
			currentProcess = head->next->data;
			while(head->next!=0x0 || currentProcess->priority > process->priority){
				head = process_list->head;
				currentProcess = head->next->data;
				index++;
			}
		}
	}
	insert(process_list, process, index);
}
