#include "dList.h"
#include <stdlib.h>

Node* createNode(void *prevAddress,void *data, void *nextAddress){
	Node *element = malloc(sizeof(Node));
	element->previous = prevAddress;
	element->data = data;
	element->next = nextAddress;
	return element;
}

DoubleList create(){
	DoubleList dList = {0,NULL,NULL};
	return dList;
}

int insertBegening(DoubleList* list,Node* head,void* data){
	Node* newNode = createNode(NULL, data, head);
    if(NULL != head)
    	head->previous = newNode;
    list->head = newNode;
    newNode->data = data;
    list->length++;
    return 1;
}

int insertAtSpecificPlace(DoubleList* list,Node* head,void* data){
	Node* newNode = createNode(head, data, head->next);
    if(head->next != NULL)
    	head->next->previous = newNode;
    head->next = newNode;
    newNode->data = data;
    list->length++;
    return 1;
}

int insert(DoubleList *list, int index, void *data){
	Node *head,*newNode;
	int i = 1;
	if(index <= -1 || index > list->length)
		return 0;
	head = list->head;
	while(i<index && head->next != NULL){
		head = head->next;
		i++;
	}
    if(index == 0)				//insert First Element
    	return insertBegening(list, head, data);
    return insertAtSpecificPlace(list, head, data);
};

void* getNodeData(DoubleList list, int index){
	int i = 0;
	Node* head = list.head;
	if(index<0 || index >= list.length)
		return NULL;
	while(i < index){
		head = head->next;
		i++;
	}
	return head->data;
}

int deleteFirst(DoubleList* list,Node* head){
	list->head = ((Node*)(list->head))->next;
	free(head);
	list->length--;
	return 1;
}

int deleteAtSpecificPlace(DoubleList* list,Node* head){
	head->previous->next = head->next;		//delete from middle of list
	if(head->next != NULL)
    	head->next->previous = head->previous;
    free(head);
    list->length--;
    return 1;
}

int delete_node(DoubleList* list,int index){
	int i;
	Node *head;
	if(index <= -1 || index >= list->length)
		return 0;
	head = list->head;
	for(i=0;i<index;i++){
		head = head->next;
	}
	if(i==0)
		return deleteFirst(list, head);
	return deleteAtSpecificPlace(list, head);
};

ListIterator iterator(DoubleList *dList){
	ListIterator it = {dList->head,dList};
	return it;
}

void* next(ListIterator it){
	if(hasNext(it))
		it.currentNode = 
	return it.currentNode->data;
}

int hasNext(ListIterator it){
	if(it.list->head == NULL) return 0;
	return it.currentNode->next != NULL;
}

void dispose(DoubleList dList){
	Node *temp;
	if(dList.head == NULL)
		return;
	temp = dList.head;
	dList.head = temp->next;
	free(temp);
	dispose(dList);
}