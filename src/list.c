#include "list.h"
#include <stdio.h>

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

void *removeCurrent(LinkedList *list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }

    ListNode *node = list->current;
    void *data = node->data;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    if (node->next != NULL) {
        list->current = node->next;
    } else {
        list->current = node->prev;
    }

    free(node);
    list->size--;

    return data;
}



void *removeFirst(LinkedList *list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }

    ListNode *node = list->head;
    void *data = node->data;
    list->head = node->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    if (list->current == node) {
        list->current = list->head;
    }

    free(node);
    list->size--;

    return data;
}

void *removeLast(LinkedList *list) {
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }

    ListNode *node = list->tail;
    void *data = node->data;
    list->tail = node->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    if (list->current == node) {
        list->current = list->tail;
    }

    free(node);
    list->size--;
    return data;
}

void removeNode(LinkedList *list, ListNode *node) {
    if (list == NULL || node == NULL) {
        return;
    }

    if (node == list->head) {
        list->head = node->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    }

    if (node == list->tail) {
        list->tail = node->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    if (list->current == node) {
        list->current = node->next != NULL ? node->next : node->prev;
    }

    list->size--;
    free(node);
}


bool prev(LinkedList *list) {
     if (list == NULL) {
        return 0;
    }

    if (list->current == list->head) {
        return 0;
    }

    list->current = list->current->prev;
    return 1;
}


bool next(LinkedList *list) {
    if (list == NULL) {
        return 0;
    }

    if (list->current == list->tail) {
        return 0;
    }

    list->current = list->current->next;
    return 1;
}

void *getCurrent(const LinkedList *list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }

    return list->current->data;
}

size_t size(const LinkedList *list) {
    if (list == NULL) {
        return 0;
    }

    return list->size;
}

void *search(LinkedList *list, bool (*comparator)(void *, void *), void *comparisonArg) {
    if (list == NULL || comparator == NULL) {
        return NULL;
    }

    ListNode *current = list->head;
    while (current != NULL) {
        if (comparator(current->data, comparisonArg)) { //compare 
            return current->data;
        }
        current = current->next;
    }

    return NULL; //no matching node found
}

ListNode* findNode(LinkedList *list, void *data) {
    if (list == NULL) return NULL;

    ListNode *current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


