#include <stdio.h>
#include "List.h"
#include <stdlib.h>

LinkedList* createList(){
    LinkedList* head = (LinkedList*)malloc(sizeof(LinkedList));
    head->head = NULL;
    head->tail = NULL;
    return (head);
}

void insertStart(LinkedList* list, char **array){
    LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->array = array;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(newNode == NULL){
        fflush(stdout);
        printf("FAILURE");
        return;
    }

    if(list->head != NULL){

        LinkedListNode *tempNode = list->head;
        newNode->next = tempNode;
        tempNode->prev = newNode;
        list->head = newNode;
    }else{
        list->head = newNode;
        list->tail = newNode;
    }
}

char** removeStart(LinkedList* list){
    if(list->head == NULL){
        return NULL;
    }

    LinkedListNode *nodeToRemove = list->head;
    if(nodeToRemove->next == NULL){
        list->head = NULL;
        return nodeToRemove->array;
    }
    else{
        LinkedListNode *tempNode = nodeToRemove->next;
        tempNode->prev = NULL;
        list->head = tempNode;
        return nodeToRemove->array;
    }
}

void insertLast(LinkedList* list, char **array){

    LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->array = array;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    }else{
        LinkedListNode *lastNode = list->tail;
        newNode->prev = lastNode;
        lastNode->next = newNode;
        list->tail = newNode;
    }
}

char** removeLast(LinkedList* list){
    if(list->head == NULL){
        return NULL;
    }

    LinkedListNode* lastNode = list->tail;
    char **array = lastNode->array;

    if(lastNode->prev == NULL){
        list->head = NULL;
        list->tail = NULL;
    }
    else{
        LinkedListNode* prevNode = lastNode->prev;
        prevNode->next = NULL;
        list->tail = prevNode;
    }

    free(lastNode);
    return array;
}

