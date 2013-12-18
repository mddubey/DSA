#include "dl_list.h"

typedef struct {
	void* data;
	int priority;
}Queue_element;

typedef DLList PQueue;

PQueue* create_queue();
int enqueue(PQueue* queue, Queue_element* element);
int dequeue(PQueue* queue);
void dispose_queue(PQueue* queue);