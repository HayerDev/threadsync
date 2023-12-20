#include "readwrite.h"

static int activeReaders = 0;
static int activeWriters = 0;

void init() {
    initMonitor(1); //initialize the monitor with the required resources
}

void beginRead() {
    enterMonitor();
    while (activeWriters > 0) { //we can exclude other reads because this doesnt cause deadlock
        waitMon(READER);  // wait if a writer is active
    }
    activeReaders++; 
    leaveMonitor();
}

void endRead() {
    enterMonitor();
    activeReaders--; 
    if (activeReaders == 0 && size(monitorList) > 0) {
        signalMon();  //signal waiting writers if no active readers left
    }
    leaveMonitor();
}

void beginWrite() {
    enterMonitor();
    while (activeReaders > 0 || activeWriters > 0) {
        waitMon(WRITER); //wait if readers or another writer is active
    }
    activeWriters = 1; 
    leaveMonitor();
}

void endWrite() {
    enterMonitor();
    activeWriters = 0;  // No more active
    signalMon(); //signal waiting readers and writers
    leaveMonitor();
}

void reader() {
    sleep(rand() % 3); // random delay before starting to read
    beginRead();
    printf("Reading...\n");
    endRead();
}

void writer() {
    sleep(rand() % 3); // random delay before starting to write
    beginWrite();
    printf("Writing...\n");
    endWrite();
}

