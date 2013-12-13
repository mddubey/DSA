#include "queue.h"
#include <memory.h>
#include <stdlib.h>

Queue* create(int length){
	Queue* queue;
	queue = (Queue*)malloc(sizeof(Queue));
	queue->elements = calloc(length, sizeof(void*));
	queue->info.front = -1;
	queue->info.rear = -1;
	queue->info.length = length;
	return queue;
}

void** getElement(Queue* queue, int index){
	return (queue->elements+index);
};

int enqueue(Queue* queue, void* element){
	if(isFull(queue)) //Queue Overflow
		return 0;
	if(queue->info.rear == -1 && queue->info.front == -1){	//First Element in Queue
		queue->info.rear++;
		queue->info.front++;
	}
	else if(queue->info.rear==queue->info.length-1)		//Rear at the End of Queue
		queue->info.rear = 0;
	else
		queue->info.rear++;
	*getElement(queue, queue->info.rear) = element;
	return 1;;
}

void* dequeue(Queue* queue){
	void* element;
	if(isEmpty(queue))
		return NULL;
	element = *(queue->elements + queue->info.front);	//address of front element
	if(queue->info.front==queue->info.rear){		//Deleting Last Element
		queue->info.rear = queue->info.front = -1;
	}
	else if(queue->info.front==queue->info.length-1)	//Front at the End of queue
		queue->info.front = 0;
	else
		queue->info.front++;
	return element;
};

int isFull(Queue* queue){
	if(queue->info.front == 0 && queue->info.rear == queue->info.length-1)
		return 1;
	if(queue->info.front==queue->info.rear+1)
		return 1;
	return 0;
}

int isEmpty(Queue* queue){
	return queue->info.front == -1;
}