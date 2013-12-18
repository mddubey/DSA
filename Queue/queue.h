typedef struct{
    void** elements;
    struct QueueInfo{
            int length;
            int rear;
            int front;
    }info;
}Queue;

Queue* create(int length);
int enqueue(Queue* queue, void* element);
void* dequeue(Queue* queue);
void** getElement(Queue* queue, int index);
int isFull(Queue* queue);
int isEmpty(Queue* queue);