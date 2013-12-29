#include "../iterator.h"

typedef struct{
	int length;
	void *head;
} DoubleList;

typedef int (*compare)(void *elementToCompare,void *element);

DoubleList* create();
int insert(DoubleList* dList,int index,void *element);
int delete_node(DoubleList* dList,int index);
void dispose(DoubleList *dList);
void* getNodeData(DoubleList list, int index);
void sort(DoubleList dList, compare cmpFunc);
Iterator getIterator(DoubleList *dList);
