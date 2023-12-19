#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <stdlib.h>

//initialize the monitor with a specified number of resources or conditions
void init(int);

//enter monitor with mutex
void enterMonitor();

//leave monitor and release mutex
void leaveMonitor();

//wait while critical area busy
void wait(int);

//signal critical area is free
void signal(int);

#endif
