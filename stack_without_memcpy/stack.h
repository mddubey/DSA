// typedef struct {
// 	void** elements;
// 	int top;
// 	int length;
// }Stack;

void* create(int length);
int push(void* stack,void* element);
// void** getElement(void* stack,int top);
void* pop(void* stack);
void* peek(void* stack);
int isEmpty(void* stack);
int isFull(void* stack);
void disposeStack(void* stack);