#include "stack.h"
#include <stdlib.h>
#include <memory.h>

void** getElement(Stack* stack,int top){
	return stack->elements + top * sizeof(void*);
};

Stack* create(int length){
	Stack* stack;
	stack = (Stack*)calloc(sizeof(Stack), 1);
	stack->elements = calloc(sizeof(void*), length);
	stack->length = length;
	stack->top = 0;
	return stack;
}

int isFull(Stack* stack){
	return stack->top==stack->length;
}

int push(Stack* stack,void* element){
	void* temp;
	if(isFull(stack)){
		temp = realloc(stack->elements, stack->length * 2 * sizeof(void*));
		if(!temp)
			return 0;
		stack->elements = temp;
		stack->length *= 2;
	}
	*(getElement(stack, stack->top++)) = element;
	return 1;
}

// void* pop(Stack* stack){
// 	if(isEmpty(stack)) return NULL;
// 	return getElement(stack,--(stack->top));
// };

// void* peek(Stack* stack){
// 	if(isEmpty(stack)) return NULL;
// 	return getElement(stack,(stack->top-1));
// }

// int isEmpty(Stack* stack){
// 	if(stack->top)
// 		return 0;
// 	return 1;
// }

