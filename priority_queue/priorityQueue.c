#include <stdlib.h>
#include "priorityQueue.h"

DLList* create_queue(){
	DLList* queue = calloc(1, sizeof(DLList));
	queue->head = NULL;
	queue->length = 0;
	return queue;
}

int enqueue(DLList *queue, Queue_element *element){
	int index;
	Node* head = queue->head;
	Queue_element* head_data;
	if(NULL == queue->head)
		return insert(queue, element, 0);
	head_data = head->data;
	if(head_data->priority>element->priority)
		return insert(queue, element, 0);
	index = 1;
	while(head->next != NULL){
		head = head->next;
		head_data = head->data;
		if(head_data->priority > element->priority){
			return insert(queue, element, index);
		}
		index++;
	}
	return insert(queue, element, index);
}