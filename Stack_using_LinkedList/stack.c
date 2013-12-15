#include "stack.h"
#include <stdlib.h>

Stack* createStack(){
	Stack* newStack = malloc(sizeof(Stack));
	newStack->list = create();
	return newStack;
};

void disposeStack(Stack* stack){
	dispose(stack->list);
	free(stack);
}
