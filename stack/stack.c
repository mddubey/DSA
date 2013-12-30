#include "stack.h"
#include <stdlib.h>
#include <memory.h>

typedef struct {
        void** elements;
        int top;
        int length;
}Stack;

void* create(int length){
        Stack* stack;
        stack = (Stack*)calloc(sizeof(Stack), 1);
        stack->elements = calloc(sizeof(void*), length);
        stack->length = length;
        stack->top = 0;
        return stack;
}

int isFull(void* stack){
        Stack* newStack = stack;
        return newStack->top==newStack->length;
}

int push(void* stack,void* element){
        Stack* newStack = stack;
        if(isFull(newStack)){
                newStack->elements = realloc(newStack->elements, newStack->length * 2 * sizeof(void*));
                newStack->length *= 2;
        }
        *(newStack->elements + newStack->top) = element;
        newStack->top++;
        return 1;
}

int isEmpty(void* stack){
        Stack* newStack = stack;
        return newStack->top == 0;
}


void* peek(void* stack){
        Stack* newStack = stack;
        if(isEmpty(newStack)) return NULL;
        return *(newStack->elements + (newStack->top - 1));
}

void* pop(void* stack){
        Stack* newStack = stack;
        void* result;
        result = peek(stack);
        newStack->top--;
        return result;
};

void disposeStack(void* stack){
        Stack* newStack = stack;
        free(newStack->elements);
        free(newStack);
}