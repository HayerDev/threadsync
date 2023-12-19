#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include <pthread.h>

typedef enum { READER, WRITER } ThreadType;

typedef struct {
    ThreadType type;
    pthread_cond_t condition;
} WaitData;

static LinkedList *monitorList;
static pthread_mutex_t monitorMutex;
static int activeReaders = 0, activeWriters = 0, waitingReaders = 0, waitingWriters = 0;

//initialize the monitor
void initMonitor(int resources);

//enter monitor with mutex
void enterMonitor();

//leave monitor and release mutex
void leaveMonitor();

//wait while critical area busy
void wait(ThreadType type);

//signal critical area is free
void signal();

//free monitor
void destroyMonitor();

#endif