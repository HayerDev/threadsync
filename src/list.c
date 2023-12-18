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
        if (current->data != NULL) { //lets overengineer a bit
            free(current->data); //free data pointer
        }
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
        newHead->data = data;
        list->head = newHead;
        list->tail = newHead;
        list->current = newHead;
        list->size = list->size + 1;
        return;
    }

    ListNode *newHead = malloc(sizeof(ListNode));
    if (newHead == NULL) {
            return; //alloc failure
    }
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
    if (newTail == NULL) {
        return; //alloc failure
    }
    newTail->data = data;
    list->tail->next = newTail;
    newTail->prev = list->tail;
    newTail->next = NULL;
    list->tail = newTail;
    list->size = list->size + 1;
    list->current = newTail;
    return;

}


void insertBefore(LinkedList *list, void *data) {
    if (list == NULL) {
        return;
    }

    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) { //allocation failure
        return;
    }

    newNode->data = data;

    if (list->size == 0 || list->current == NULL) {
        newNode->prev = NULL;
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
    } else {
        newNode->prev = list->current->prev;
        newNode->next = list->current;
        if (list->current->prev != NULL) {
            list->current->prev->next = newNode;
        } else {
            list->head = newNode; //new node becomes new head
        }
        list->current->prev = newNode;
    }
    list->size++;
}

void addAftercurrent(LinkedList *list, void *data){
    if (list == NULL) {
        return;
    }

    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) { //allocation failure
        return;
    }

    newNode->data = data;

    if (list->size == 0 || list->current == NULL) {
        newNode->prev = NULL;
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
    } else {
        newNode->prev = list->current;
        newNode->next = list->current->next;
        if (list->current->next != NULL) {
            list->current->next->prev = newNode;
        } else {
            list->tail = newNode; // new node becomes new tail
        }
        list->current->next = newNode;
    }
    list->size++;
}
