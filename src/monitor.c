#include "monitor.h"

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

void wait(ThreadType type) {
    WaitData *data = malloc(sizeof(WaitData));
    data->type = type;
    pthread_cond_init(&data->condition, NULL);
    append(monitorList, data);

    if (type == READER) {
        waitingReaders++;
        while (activeWriters > 0 || (waitingWriters > 0 && activeReaders == 0)) {
            pthread_cond_wait(&data->condition, &monitorMutex);
        }
        waitingReaders--;
        activeReaders++;
    } else { //WRITER
        waitingWriters++;
        while (activeReaders > 0 || activeWriters > 0) {
            pthread_cond_wait(&data->condition, &monitorMutex);
        }
        waitingWriters--;
        activeWriters++;
    }
}

void signal() {
    if (monitorList->size > 0) {
        ListNode *node = monitorList->head;
        while (node != NULL) {
            WaitData *data = (WaitData *)node->data;
            if (data->type == READER && waitingWriters == 0) {
                pthread_cond_signal(&data->condition);
                break;
            } else if (data->type == WRITER && activeReaders == 0 && activeWriters == 0) {
                pthread_cond_signal(&data->condition);
                break;
            }
            node = node->next;
        }
    }
}

void destroyMonitor() {
    ListNode *node = monitorList->head;
    while (node != NULL) {
        WaitData *data = (WaitData *)node->data;
        pthread_cond_destroy(&data->condition);
        free(data);
        node = node->next;
    }
    destroy(monitorList);
    pthread_mutex_destroy(&monitorMutex);
}
