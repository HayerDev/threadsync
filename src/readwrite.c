#include "readwrite.h"

void init() {
    initMonitor(1); //initialize the monitor with the required resources
}

void beginRead() {
    enterMonitor();
    while (activeWriters > 0) { //we can exclude other reads because this doesnt cause deadlock
        wait(READER); // wait if a writer is active
    }
    activeReaders++; 
    leaveMonitor();
}

void endRead() {
    enterMonitor();
    activeReaders--; 
    if (activeReaders == 0) {
        signal(); //signal waiting writers if no active readers left
    }
    leaveMonitor();
}

void beginWrite() {
    enterMonitor();
    while (activeReaders > 0 || activeWriters > 0) {
        wait(WRITER); //wait if readers or another writer is active
    }
    activeWriters = 1; 
    leaveMonitor();
}

void endWrite() {
    enterMonitor();
    activeWriters = 0; // No more active 
    signal(); //signal waiting readers and writers
    leaveMonitor();
}

void reader() {
    beginRead();
    //perform reading operations...
    endRead();
}

void writer() {
    beginWrite();
    //perform writing operations...
    endWrite();
}
