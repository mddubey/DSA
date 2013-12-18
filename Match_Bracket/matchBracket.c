#include "matchBracket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./include/stack.h"


ErrorMsg createResult(int isError,int index,char bracket,Stack* stack){
    ErrorMsg result;
    result.isError = isError;
    result.index = index;
    result.bracket = bracket;
    free(stack->elements);
    free(stack);
    return result;
};

char getOpeningBracket(char letter){
    if (letter==')') return '(';
    if (letter=='}') return '{';
    if (letter==']') return '[';
    return '\0';
};

ErrorMsg areBracketsMatching(const char* input){
    Stack* stack;
    int index,limit;
    ErrorMsg result;
    char element;
    stack = create(strlen(input), sizeof(char));
    for(index=0;index<strlen(input);index++){
        element = input[index];
        if(element=='{'|| element=='[' || element=='(')
                push(stack, (void*)&element);

        if(getOpeningBracket(element)){
            if(isEmpty(stack))
                return createResult(1, index+1, element,stack);
            if(*(char*)peek(stack)==getOpeningBracket(element)){
                pop(stack);
            }
            else
                return createResult(1, index+1, *(char*)peek(stack),stack);
        }
    }
    if(stack->top==0)
        return createResult(0, -1, '\0', stack);
    return createResult(1, 0, '\0',stack);
}