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
	int i;
	if(index <= -1 || index > list->length)
		return 0;
	head = list->head;
    for (i = 0; i < index ; ++i){
        if(head->next != NULL)
                head = head->next;
    }
    if(index == 0){				//insert First Element
	    newNode = createNode(NULL, NULL);
	    if(NULL != head){
	    	newNode->next = head;
	    	head->prev = newNode;
	    }
	    list->head = newNode;
	    newNode->data = data;
	    list->length++;
	    return 1;
    }
    if(index == list->length){		//insert last
        newNode = createNode(head, NULL);
        head->next = newNode;
        newNode->data = data;
        list->length++;
        return 1;
    }
    newNode = createNode(head->prev, head);	// insert middle
    head->prev->next = newNode;
    newNode->data = data;
    list->length++;
    return 1;
};

int deleteNode(DLList* list,int index){
	int i;
	Node *head, *deletedNode;
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
	if(i==list->length-1){	//delete the last node
		head->prev->next = NULL;
		free(head);
		list->length--;
		return 1;
	}
	head->prev->next = head->next;
    head->next->prev = head->prev;
    free(head);
    list->length--;
    return 1;
};