typedef struct node{
	struct node* next;
	struct node* prev;
	void* data;
}Node;

typedef struct list{
	Node* head;
	int length;
}DLList;

DLList* create();
Node* createNode(Node *prevAddress, Node *nextAddress);
int insert(DLList* list,void* data,int index);
int deleteNode(DLList* list,int index);