typedef struct process{
        char name[256];
        int runTime;
        int priority;
        struct process *next;
} Process;

typedef struct{
        Process *head;
        int length;
} Scheduler;

Scheduler* createScheduler();
Process* createProcess(char* name,int runTime,int priority);
int addProcess(Scheduler *list,Process *process);
int endProcess(Scheduler *list);
void dispose(Scheduler *list);