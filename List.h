#ifndef ENTRY
#define ENTRY

typedef struct LinkedListNode{
    char **array;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode; 

typedef struct{
    LinkedListNode* head;
    LinkedListNode* tail;
}LinkedList;

LinkedList* createList();
void insertStart(LinkedList* list, char **array);
char** removeStart(LinkedList* list);
void insertLast(LinkedList* list, char **array);
char** removeLast(LinkedList* list);

#endif