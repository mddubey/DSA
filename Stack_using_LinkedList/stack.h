#include "./include/dl_list.h"

typedef struct{
	DLList* list;
}Stack;

Stack* createStack();
int push(Stack* stack, void* element);
void disposeStack(Stack* stack);