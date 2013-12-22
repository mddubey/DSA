#include "dl_list.h"
#include <stdlib.h>

DLList* create(){
	DLList* list;
	list = (DLList*)malloc(sizeof(DLList));
	list->head = NULL;
	list->length = 0;
	return list;
};

Node* createNode(Node *prevAddress, Node *nextAddress){
   	Node *element = malloc(sizeof(Node));
    element->prev = prevAddress;
    element->next = nextAddress;
    return element;
}

int insertBegening(DLList* list,Node* head,void* data){
	Node* newNode = createNode(NULL, head);
    if(NULL != head)
    	head->prev = newNode;
    list->head = newNode;
    newNode->data = data;
    list->length++;
    return 1;
}

int insertAtSpecificPlace(DLList* list,Node* head,void* data){
	Node* newNode = createNode(head, head->next);
    if(head->next != NULL)
    	head->next->prev = newNode;
    head->next = newNode;
    newNode->data = data;
    list->length++;
    return 1;
}

int insert(DLList *list, void *data, int index){
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

void* getNodeData(DLList* list, int index){
	int i = 0;
	Node* head = list->head;
	if(index<0 || index >= list->length)
		return NULL;
	while(i < index){
		head = head->next;
		i++;
	}
	return head->data;
}

int deleteFirst(DLList* list,Node* head){
	list->head = list->head->next;
	free(head);
	list->length--;
	return 1;
}

int deleteAtSpecificPlace(DLList* list,Node* head){
	head->prev->next = head->next;		//delete from middle of list
	if(head->next != NULL)
    	head->next->prev = head->prev;
    free(head);
    list->length--;
    return 1;
}

int deleteNode(DLList* list,int index){
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

void dispose(DLList* list){
	Node *head;
	head = list->head;
	while(head!=NULL){
		list->head = head->next;
		head->next = head->prev = NULL;
		free(head);
		head = list->head;
	}
	free(list->head);
}