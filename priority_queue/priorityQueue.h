#include "./include/dl_list.h"

typedef struct {
	void* data;
	int priority;
}Queue_element;

DLList* create_queue();
int enqueue(DLList* queue, Queue_element* element);