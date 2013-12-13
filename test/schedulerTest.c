#include "testUtils.h"
#include "scheduler.h"
#include <stdlib.h>
#include <string.h>

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed
Scheduler *list;
void tearDown(){
    dispose(list);
}
void test_create_a_new_scheduler_list(){
    Scheduler expected = {NULL,0};
    list = createScheduler();
    ASSERT(list->head == expected.head);
    ASSERT(list->length == expected.length);
}

void test_inserts_a_new_process_in_the_list(){
    Process* process = createProcess("Mozila", 200, 1);
    list = createScheduler();
    ASSERT(1 == addProcess(list, process));
    ASSERT(list->head == process);
    ASSERT(list->head->next == NULL);
}
void test_add_process_with_priority_higher_than_first_process(){
    Process* p1 = createProcess("Chrome", 100, 2);
    Process* p2 = createProcess("Mozila", 100, 1);
    list = createScheduler();
    ASSERT(1 == addProcess(list, p1));
    ASSERT(2 == addProcess(list, p2));
    ASSERT(list->head == p2);
    ASSERT(list->head->next == p1);
}

void test_insert_process_into_acending_order_of_there_priorities(){
    Process *second,*third;
    Process* process1 = createProcess("Chrome", 100, 3);
    Process* process2 = createProcess("Mozila", 300, 1);
    Process* process3 = createProcess("Safari", 200, 2);
    list = createScheduler();
    ASSERT(1 == addProcess(list, process1));
    ASSERT(2 == addProcess(list, process2));
    ASSERT(3 == addProcess(list, process3));
    ASSERT(list->head == process2);
    second = list->head->next;
    third = second->next;
    ASSERT(second == process3);
    ASSERT(third == process1);
    ASSERT(third->next == NULL);
}

void test_inserts_the_lowest_priority_to_last_in_queue(){
    Process *second,*third;
    Process* process1 = createProcess("Chrome", 100, 8);
    Process* process2 = createProcess("Mozila", 300, 1);
    Process* process3 = createProcess("Safari", 200, 2);
    list = createScheduler();
    ASSERT(1 == addProcess(list, process1));
    ASSERT(2 == addProcess(list, process2));
    ASSERT(3 == addProcess(list, process3));
    ASSERT(list->head == process2);
    second = list->head->next;
    third = second->next;
    ASSERT(second == process3);
    ASSERT(third == process1);
    ASSERT(third->next == NULL);
}