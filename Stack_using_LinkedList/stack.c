#include "stack.h"
#include <stdlib.h>

Stack* createStack(){
	Stack* newStack = malloc(sizeof(Stack));
	newStack->list = create();
	return newStack;
};

int push(Stack* stack, void* element){
	return insert(stack->list, element, stack->list->length);
}

int pop(Stack* stack){
	return deleteNode(stack->list, stack->list->length - 1);
}

int isEmpty(Stack* stack){
	return 0 == stack->list->length;
}

void* peek(Stack *stack){
	Node* head;
	if(isEmpty(stack))
		return NULL;
	head = stack->list->head;
	while(head->next!=NULL){
		head = head->next;
	}
	return head->data;
}

void disposeStack(Stack* stack){
	dispose(stack->list);
	free(stack);
}
