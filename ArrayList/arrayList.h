#include "../iterator.h"
typedef struct {
	void** base;
	int capacity;
	int length;
} ArrayList;

typedef int Comparator (void* first,void* second);

ArrayList create(int capacity);

int insert(ArrayList *list, int index, void* data);
void* get(ArrayList list, int index);
int remove(ArrayList* list, int index);
int add(ArrayList* list, void* data);
int getIndex(ArrayList list, void* data, Comparator* areEqual);
Iterator getIterator(ArrayList* list);
void dispose(ArrayList *list);