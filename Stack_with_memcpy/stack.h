typedef struct {
	void* elements;
	int top;
	int length;
	int elementSize;
}Stack;

Stack* create(int length,int elementSize);
int push(Stack* s,void* element);

void* pop(Stack* s);
void* peek(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);