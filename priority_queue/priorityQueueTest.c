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

void test_creates_a_new_queue(){
	queue = create_queue();
	ASSERT(queue->head == NULL);
	ASSERT(0 == queue->length);
}

void test_adds_the_element_at_the_starting_of_queue(){
	Queue_element* element = malloc(sizeof(Queue_element));
	int * num = malloc(sizeof(int));
	*num = 10;element[0].data = num;element[0].priority = 1;
	queue = create_queue();
	enqueue(queue, element);
	ASSERT(areElementsEqual(*element, *(Queue_element*)queue->head->data));
}

void test_adds_the_element_first_having_lower_priority(){
	Queue_element* elements = malloc(sizeof(Queue_element)*2);
	int * nums = malloc(sizeof(int)*2);
	nums[0] = 10;elements[0].data = &nums[0];elements[0].priority = 1;
	nums[1] = 11;elements[1].data = &nums[1];elements[1].priority = 2;
	queue = create_queue();
	enqueue(queue, &elements[1]);
	enqueue(queue, &elements[0]);
	ASSERT(areElementsEqual(elements[0], *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(elements[1], *(Queue_element*)queue->head->next->data));
}

void test_adds_the_element_in_middle_according_to_priority(){
	Queue_element* elements = malloc(sizeof(Queue_element)*3);
	int * nums = malloc(sizeof(int)*3);
	nums[0] = 10;elements[0].data = &nums[0];elements[0].priority = 1;
	nums[1] = 11;elements[1].data = &nums[1];elements[1].priority = 3;
	nums[2] = 22;elements[2].data = &nums[2];elements[2].priority = 2;
	queue = create_queue();
	enqueue(queue, &elements[1]);
	enqueue(queue, &elements[0]);
	enqueue(queue, &elements[2]);
	ASSERT(areElementsEqual(elements[0], *(Queue_element*)queue->head->data));
	ASSERT(areElementsEqual(elements[2], *(Queue_element*)queue->head->next->data));
	ASSERT(areElementsEqual(elements[1], *(Queue_element*)queue->head->next->next->data));
}
