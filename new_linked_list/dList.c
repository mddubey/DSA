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

int hasNextInList(Iterator *it){
	DoubleList dList;
	if(NULL == it->list) return 0;
	dList = *(DoubleList*)it->list;
	if(it->position >= dList.length) return 0;
	return 1;
}

void* nextInList(Iterator* it){
	int i;
	Node* head;
	if(!hasNextInList(it)) return NULL;
	head = ((DoubleList*)(it->list))->head;
	for(i = 0; i<it->position; i++){
		head = head->next;
	};
	it->position++;
	return head->data;
}

Iterator getIterator(DoubleList *dList){
	Iterator listIterator;
	listIterator.position = 0;
	listIterator.list = dList;
	listIterator.hasNext = &hasNextInList;
	listIterator.next = &nextInList;
	return listIterator;
}

void dispose(DoubleList *dList){
	Node *temp;
	if(!dList || dList->head == NULL)
		return;
	temp = dList->head;
	dList->head = temp->next;
	free(temp);
	dispose(dList);
}