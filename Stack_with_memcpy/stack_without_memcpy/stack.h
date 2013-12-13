typedef struct {
	void** elements;
	int top;
	int length;
}Stack;

typedef char String_256[256];
Stack* create(int length);
int push(Stack* s,void* element);
void** getElement(Stack* stack,int top);
// void* pop(Stack* s);
// void* peek(Stack* s);
// int isEmpty(Stack* s);
int isFull(Stack* s);