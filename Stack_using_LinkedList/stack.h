#include "./include/dl_list.h"

typedef struct{
	DLList* list;
}Stack;

Stack* createStack();
int push(Stack* stack, void* element);
int pop(Stack* stack);
void* peek(Stack* stack);
void disposeStack(Stack* stack);