typedef struct{
	void** elements;
	struct QueueInfo{
		int length;
		int rear;
		int front;
	}info;
}Queue;

typedef char String_256[256];
Queue* create(int length);
int enqueue(Queue* queue, void* element);
void* dequeue(Queue* queue);
void** getElement(Queue* queue, int index);
int isFull(Queue* queue);
int isEmpty(Queue* queue);