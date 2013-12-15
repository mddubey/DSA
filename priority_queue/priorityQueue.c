#include <stdlib.h>
#include "priorityQueue.h"

PQueue* create_queue(){
	PQueue* queue = calloc(1, sizeof(PQueue));
	return queue;
}

int enqueue(PQueue *queue, Queue_element *element){
	int index = 1;
	Node* head = queue->head;
	Queue_element* head_data;
	if(NULL == queue->head)
		return insert(queue, element, 0);
	head_data = head->data;
	if(head_data->priority > element->priority)
		return insert(queue, element, 0);
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

int dequeue(PQueue* queue){
	return deleteNode(queue, 0);
}

void dispose_queue(PQueue* queue){
	dispose(queue);
}