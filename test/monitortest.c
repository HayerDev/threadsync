#include "../src/readwrite.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//reader thread function
void *readerThread(void *arg) {
    printf("Reader thread started\n");
    reader();
    printf("Reader thread finished\n");
    return NULL;
}

//writer thread function
void *writerThread(void *arg) {
    printf("Writer thread started\n");
    writer();
    printf("Writer thread finished\n");
    return NULL;
}

int main() {
    // initialize the monitor
    init();

    srand(time(NULL)); //initialize random number generator

    const int numReaders = 5;
    const int numWriters = 5;

    pthread_t readers[numReaders], writers[numWriters];

    //interleave creation of reader and writer threads (as best as possible)
    int maxThreads = numReaders > numWriters ? numReaders : numWriters;
    for (int i = 0; i < maxThreads; ++i) {
        if (i < numReaders) {
            sleep(rand() % 3); //random delay before starting thread
            if (pthread_create(&readers[i], NULL, readerThread, NULL) != 0) {
                perror("Failed to create reader thread");
                return 1;
            }
        }
        if (i < numWriters) {
            sleep(rand() % 3); //random delay before starting thread
            if (pthread_create(&writers[i], NULL, writerThread, NULL) != 0) {
                perror("Failed to create writer thread");
                return 1;
            }
        }
    }

    // wait for all threads to complete
    for (int i = 0; i < numReaders; ++i) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < numWriters; ++i) {
        pthread_join(writers[i], NULL);
    }

    printf("All reader and writer threads have completed\n");

    destroyMonitor();

    return 0;
}