#include "../src/list.h"
#include <stdio.h>

//comparator search
bool intComparator(void *data, void *arg) {
    return *(int*)data == *(int*)arg;
}

//tests

void testPrependAppend() {
    LinkedList *list = create();
    int data1 = 10, data2 = 20, data3 = 30, data4 = 40;

    prepend(list, &data1); //10
    append(list, &data2); //10, 20 
    next(list);
    insertBefore(list, &data3); //list: 10, 30, 20
    addAftercurrent(list, &data4); //list: 10, 30, 20, 40

    if (*(int *)getCurrent(list) != 20 || size(list) != 4 || *(int *)list->head->data != 10 || *(int *)list->tail->data != 40 ) {
        printf("Error in testPrependAppend\n");
        return;
    }

    removeLast(list); //10, 30, 20 
    removeCurrent(list);// 10, 30 

    if (*(int *)getCurrent(list) != 30 || size(list) != 2 || *(int *)list->head->data != 10 || *(int *)list->tail->data != 30 ) {
        printf("Error in testPrependAppend\n");
        return;
    }

    destroy(list);
    printf("Passed testPrependAppend\n");
    
}

void testRemove() {
    LinkedList *list = create();
    int data1 = 10, data2 = 20;

    append(list, &data1);
    append(list, &data2);
    removeCurrent(list);
    removeLast(list);

    if (size(list) != 0) {
        printf("Error in testRemove\n");
        return;
    }

    destroy(list);
    printf("Passed testRemove\n");
}

void testPrevNext() {
    LinkedList *list = create();
    int data1 = 10, data2 = 20;

    append(list, &data1);
    append(list, &data2);
    prev(list);

    if (*(int *)getCurrent(list) != 10) {
        printf("Error in testPrevNext\n");
        return;
    }

    next(list);
    if (*(int *)getCurrent(list) != 20) {
        printf("Error in testPrevNext\n");
        return;
    }

    destroy(list);
    printf("Passed testPrevNext\n");
}

void testSearch() {
    LinkedList *list = create();
    int data1 = 10, data2 = 20, searchArg = 20;

    append(list, &data1);
    append(list, &data2);

    int *found = (int *)search(list, intComparator, &searchArg);
    if (found == NULL || *found != 20) {
        printf("Error in testSearch\n");
        return;
    }

    destroy(list);
    printf("Passed testSearch\n");
}

//run tests
int main(int argc, char *argv[]) {
    testPrependAppend();
    testRemove();
    testPrevNext();
    testSearch();

    printf("Tests complete, end of run\n");

    return 0;
}
