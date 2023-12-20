#include "monitor.h"

LinkedList *monitorList; 
pthread_mutex_t monitorMutex; 

//helper function to create a new WaitData
static WaitData *newWaitData(ThreadType type) {
    WaitData *waitData = malloc(sizeof(WaitData));
    if (!waitData) {
        perror("Failed to allocate WaitData");
        exit(EXIT_FAILURE);
    }
    waitData->type = type;
    pthread_cond_init(&waitData->condition, NULL);
    return waitData;
}

void initMonitor(int resources) {
    monitorList = create();
    pthread_mutex_init(&monitorMutex, NULL);
}

void enterMonitor() {
    pthread_mutex_lock(&monitorMutex);
}

void leaveMonitor() {
    pthread_mutex_unlock(&monitorMutex);
}

void waitMon(ThreadType type) {
    WaitData *waitData = newWaitData(type);
    append(monitorList, waitData);
    pthread_cond_wait(&waitData->condition, &monitorMutex);
}

void signalMon() {
    if (size(monitorList) > 0) {
        ListNode *first = monitorList->head;
        WaitData *waitData = (WaitData *)first->data;
        pthread_cond_signal(&waitData->condition);
        removeFirst(monitorList);
    }
}

void destroyMonitor() {
    while (size(monitorList) > 0) {
        ListNode *first = monitorList->head;
        WaitData *waitData = (WaitData *)removeFirst(monitorList);
        pthread_cond_destroy(&waitData->condition);
        free(waitData);
    }
    destroy(monitorList);
    pthread_mutex_destroy(&monitorMutex);
}

