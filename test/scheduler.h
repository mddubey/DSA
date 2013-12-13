#include "./include/dl_list.h"

typedef char String_256[256];
typedef struct{
        int priority;
        int runTime;
        String_256 name;
}Process;

void addProcess(DLList* process_list, Process* process);