#include "./include/stack.h"

typedef struct{
	int isError;
	int index;
	char bracket;
}ErrorMsg;

ErrorMsg popElement(char element,int index,Stack* stack);
ErrorMsg startMatch(const char* input);
ErrorMsg createResult(int isError,int index,char bracket,Stack* stack);
int isCloseBracket(char letter);
char getOpeningBracket(char letter);