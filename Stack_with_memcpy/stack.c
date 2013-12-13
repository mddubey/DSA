#include "stack.h"
#include <stdlib.h>
#include <memory.h>

void* getElement(Stack* stack,int top){
	return stack->elements+top*stack->elementSize;
};

Stack* create(int length, int elementSize){
	Stack* stack;
	stack = (Stack*)calloc(sizeof(Stack), 1);
	stack->elements = calloc(elementSize, length);
	stack->elementSize = elementSize;
	stack->length = length;
	stack->top = 0;
	return stack;
}

int push(Stack* stack,void* element){
	void* temp;
	if(isFull(stack)){
		temp = realloc(stack->elements, stack->length * 2 * stack->elementSize);
		if(!temp)
			return 0;
		stack->elements = temp;
		stack->length *= 2;
	}
	memcpy(getElement(stack,stack->top++),element,stack->elementSize);
	return 1;
}

void* pop(Stack* stack){
	if(isEmpty(stack)) return NULL;
	return getElement(stack,--(stack->top));
};

void* peek(Stack* stack){
	if(isEmpty(stack)) return NULL;
	return getElement(stack,(stack->top-1));
}

int isEmpty(Stack* stack){
	if(stack->top)
		return 0;
	return 1;
}

int isFull(Stack* stack){
	if(stack->top==stack->length)
		return 1;
	return 0;
}
