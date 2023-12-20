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

extern LinkedList *monitorList;
extern pthread_mutex_t monitorMutex; 

//initialize the monitor
void initMonitor(int resources);

//enter monitor with mutex
void enterMonitor();

//leave monitor and release mutex
void leaveMonitor();

//wait while critical area busy
void waitMon(ThreadType type); //rename due to conflict

//signal critical area is free
void signalMon(); //rename due to conflict

//free monitor
void destroyMonitor();

#endif