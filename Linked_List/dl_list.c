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
    if(index == 0){				//insert First Element
	    newNode = createNode(NULL, head);
	    if(NULL != head)
	    	head->prev = newNode;
	    list->head = newNode;
	    newNode->data = data;
	    list->length++;
	    return 1;
    }
    newNode = createNode(head, head->next);	// insert at specified place
    if(head->next != NULL)
    	head->next->prev = newNode;
    head->next = newNode;
    newNode->data = data;
    list->length++;
    return 1;
};

int deleteNode(DLList* list,int index){
	int i;
	Node *head;
	if(index <= -1 || index >= list->length)
		return 0;
	head = list->head;
	for(i=0;i<index;i++){
		head = head->next;
	}
	if(i==0){		//delete first node
		list->head = list->head->next;
		free(head);
		list->length--;
		return 1;
	}
	head->prev->next = head->next;		//delete from middle of list
	if(head->next != NULL)
    	head->next->prev = head->prev;
    free(head);
    list->length--;
    return 1;
};