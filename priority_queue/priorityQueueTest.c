#include <stdlib.h>
#include "testUtils.h"
#include "priorityQueue.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

DLList* queue;
void tearDown(){
	dispose(queue);
}

int areElementsEqual(Queue_element expected, Queue_element actual){
	return expected.data == actual.data && expected.priority == actual.priority;
}

Queue_element* createQueueElement(void* data,int priority){
	Queue_element* element = malloc(sizeof(Queue_element));
	element->data = data;
	element->priority = priority;
	return element;
}

void test_creates_a_new_queue(){
	queue = create_queue();
	ASSERT(queue->head == NULL);
	ASSERT(0 == queue->length);
}

void test_adds_the_element_at_the_starting_of_queue(){
	int * num = malloc(sizeof(int));
	Queue_element* element = createQueueElement(num, 1);
	*num = 10;
	// element = 
	queue = create_queue();
	enqueue(queue, element);
	ASSERT(areElementsEqual(*element, *(Queue_element*)queue->head->data));
}

void test_adds_the_element_first_having_lower_priority(){
	int * nums = malloc(sizeof(int)*2);
	Queue_element* element1 = createQueueElement(&nums[0], 1);
	Queue_element* element2 = createQueueElement(&nums[1], 2);
	nums[0] = 10;
	nums[1] = 11;
	queue = create_queue();
	enqueue(queue, element1);
	enqueue(queue, element2);
	ASSERT(areElementsEqual(*element1, *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(*element2, *(Queue_element*)queue->head->next->data));
}

void test_adds_the_element_in_middle_according_to_priority(){
	Node* result;
	int * nums = malloc(sizeof(int)*3);
	Queue_element* element1 = createQueueElement(&nums[0], 1);
	Queue_element* element2 = createQueueElement(&nums[1], 3);
	Queue_element* element3 = createQueueElement(&nums[2], 2);
	nums[0] = 10;nums[1] = 11;nums[2] = 22;
	queue = create_queue();
	enqueue(queue, element2);
	enqueue(queue, element1);
	enqueue(queue, element3);
	result = queue->head->next;
	ASSERT(areElementsEqual(*element1, *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(*element3, *(Queue_element*)result->data));
	result = result->next;
	ASSERT(areElementsEqual(*element2, *(Queue_element*)result->data));
}

void test_adds_the_element_end_of_the_queue(){
	Node* result;
	int * nums = malloc(sizeof(int)*3);
	Queue_element* element1 = createQueueElement(&nums[0], 2);
	Queue_element* element2 = createQueueElement(&nums[1], 3);
	Queue_element* element3 = createQueueElement(&nums[2], 2);
	nums[0] = 10;nums[1] = 11;nums[2] = 22;
	queue = create_queue();
	enqueue(queue, element1);
	enqueue(queue, element3);
	enqueue(queue, element2);
	result = queue->head->next;
	ASSERT(areElementsEqual(*element1, *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(*element3, *(Queue_element*)result->data));
	result = result->next;
	ASSERT(areElementsEqual(*element2, *(Queue_element*)result->data));
}

void test_adds_the_element_end_of_the_queue_doubles(){
	Node* result;
	double * nums = malloc(sizeof(double)*3);
	Queue_element* element1 = createQueueElement(&nums[0], 2);
	Queue_element* element2 = createQueueElement(&nums[1], 3);
	Queue_element* element3 = createQueueElement(&nums[2], 2);
	nums[0] = 10.0;nums[1] = 11.0;nums[2] = 22.0;
	queue = create_queue();
	enqueue(queue, element1);
	enqueue(queue, element3);
	enqueue(queue, element2);
	result = queue->head->next;
	ASSERT(areElementsEqual(*element1, *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(*element3, *(Queue_element*)result->data));
	result = result->next;
	ASSERT(areElementsEqual(*element2, *(Queue_element*)result->data));
}

void test_adds_the_element_end_of_the_queue_characters(){
	Node* result;
	char * chars = malloc(sizeof(char)*3);
	Queue_element* element1 = createQueueElement(&chars[0], 2);
	Queue_element* element2 = createQueueElement(&chars[1], 3);
	Queue_element* element3 = createQueueElement(&chars[2], 2);
	chars[0] = 'a';chars[1] = 'e';chars[2] = 'b';
	queue = create_queue();
	enqueue(queue, element1);
	enqueue(queue, element3);
	enqueue(queue, element2);
	result = queue->head->next;
	ASSERT(areElementsEqual(*element1, *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(*element3, *(Queue_element*)result->data));
	result = result->next;
	ASSERT(areElementsEqual(*element2, *(Queue_element*)result->data));
}

// typedef char String[256];

// void test_adds_the_element_end_of_the_queue_Strings(){
// 	Node* result;
// 	String * names = malloc(sizeof(String)*3);
// 	Queue_element* element1 = createQueueElement(&names[0], 2);
// 	Queue_element* element2 = createQueueElement(&names[1], 3);
// 	Queue_element* element3 = createQueueElement(&names[2], 2);
// 	names[0] = "afads";names[1] = 'e';names[2] = 'b';
// 	queue = create_queue();
// 	enqueue(queue, element1);
// 	enqueue(queue, element3);
// 	enqueue(queue, element2);
// 	result = queue->head->next;
// 	ASSERT(areElementsEqual(*element1, *(Queue_element*)queue->head->data));
// 	ASSERT(areElementsEqual(*element3, *(Queue_element*)result->data));
// 	result = result->next;
// 	ASSERT(areElementsEqual(*element2, *(Queue_element*)result->data));
// }

void test_removes_the_element_from_starting_of_the_queue(){
	Node* result;
	int * nums = malloc(sizeof(int)*3);
	Queue_element* element1 = createQueueElement(&nums[0], 2);
	Queue_element* element2 = createQueueElement(&nums[1], 3);
	Queue_element* element3 = createQueueElement(&nums[2], 2);
	nums[0] = 10;nums[1] = 11;nums[2] = 22;
	queue = create_queue();
	enqueue(queue, element1);
	enqueue(queue, element3);
	enqueue(queue, element2);
	dequeue(queue);
	result = queue->head->next;
	ASSERT(areElementsEqual(*element3, *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(*element2, *(Queue_element*)result->data));
}