#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

// define the node structure for the  linked list
typedef struct ListNode {
    void *data;              //pointer to the data stored in the node
    struct ListNode *next;   //pointer to the next node in the list
    struct ListNode *prev;   //pointer to the previous node in the list
} ListNode;

// Define the structure for the  linked list itself
typedef struct {
    ListNode *head;          //pointer to the first node in the list
    ListNode *tail;          //pointer to the last node in the list
    ListNode *current;       //pointer to the current node in the list
    size_t size;             //number of elements in the list
} LinkedList;

//function prototypes for operations on the  linked list

//create a new, empty linked list
LinkedList *create();

// delete the  linked list and free its memory
void destroy(LinkedList *list);

//insert a new element at the beginning of the list
void prepend(LinkedList *list, void *data);

//insert a new element at the end of the list
void append(LinkedList *list, void *data);

//insert a new element before the current element
void insertBefore(LinkedList *list, void *data);

//insert a new element after the current element
void addAftercurrent(LinkedList *list, void *data);

//remove the current element from the list
void *removeCurrent(LinkedList *list);

//remove and return the element at the beginning of the list
void *removeFirst(LinkedList *list);

//remove and return the element at the end of the list
void *removeLast(LinkedList *list);

//move the current pointer to the previous node
bool prev(LinkedList *list);

// move the current pointer to the next node
bool next(LinkedList *list);

//get the data of the current node
void *getCurrent(const LinkedList *list);

// get the number of elements in the list
size_t size(const LinkedList *list);

// search the list and return the first node for which the comparator returns true
void *search(LinkedList *list, bool (*comparator)(void *, void *), void *comparisonArg);

#endif // LIST_H
