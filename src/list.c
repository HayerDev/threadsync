#include "list.h"

LinkedList *create() {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL; // failed to allocate memory
    }
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->size = 0;
    return list;
}

void destroy(LinkedList *list) {
    if (list == NULL) {
        return;
    }
    
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current); //deallocate node
        current = next;
    }
    free(list); //deallocate list
}

void prepend(LinkedList *list, void *data) {
    if (list == NULL) {
        return;
    }

    else if(list->size == 0) {
        ListNode *newHead = malloc(sizeof(ListNode));
        if (newHead == NULL) {
            return; //alloc failure
        }
        newhead->data = data;
        list->head = newHead;
        list->tail = newHead;
        list->current = newHead;
        list->size = list->size + 1;
        return;
    }

    ListNode *newHead = malloc(sizeof(ListNode));
    newHead->data = data;
    list->head->prev = newHead;
    newHead->prev = NULL;
    newHead->next = list->head;
    list->head = newHead;
    list->size = list->size + 1;
    list->current = newHead;
    return;

}

void append(LinkedList *list, void *data) {
    if (list == NULL) {
        return;
    }

    else if(list->size == 0) {
        ListNode *newTail = malloc(sizeof(ListNode));
        if (newTail == NULL) {
            return; //alloc failure
        }
        newTail->data = data;
        list->head = newTail;
        list->tail = newTail;
        list->current = newTail;
        list->size = list->size + 1;
        return;

    }

    ListNode *newTail = malloc(sizeof(ListNode));
    newTail->data = data;
    list->tail->next = newTail;
    newTail->prev = list->tail;
    newTail->next = NULL;
    list->tail = newTail;
    list->size = list->size + 1;
    list->current = newTail;
    return;

}