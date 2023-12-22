"# threadsync" 


# Project Documentation: Thread Synchronization Using Monitor for the Reader-Writer Problem
## Introduction
This project demonstrates the implementation of thread synchronization using a monitor in the context of the classic Reader-Writer problem. It is a concurrent programming project that focuses on achieving synchronization among multiple threads accessing shared resources. The solution is implemented in C and utilizes a custom linked list for queue management and a monitor for synchronization.

## What is the Reader-Writer Problem?
The Reader-Writer problem is a classic example in computer science used to illustrate synchronization challenges in concurrent programming. The problem involves managing access to a shared resource (like a database or file) by multiple readers and writers concurrently. The challenge is to allow multiple readers to read simultaneously while ensuring exclusive access for writers.

## Key Concepts
1. Threads: Lightweight processes that can run concurrently. This project creates multiple reader and writer threads to simulate concurrent access to a shared resource.

2. Monitors: A synchronization construct that allows threads to have both mutual exclusion (mutex) and the ability to wait (condition variables) for a certain condition to become true. Monitors are used to control access to the shared resource.

3. Deadlock: A situation where two or more threads are unable to proceed because each is waiting for the other to release a resource. This project aims to avoid deadlocks through careful monitor and condition variable management.

4. Linked List: A dynamic data structure used to implement queues in this project. The list manages threads waiting to access the shared resource.

## Project Structure
### Important Headers
- src/
	- list.h: Header file for the linked list implementation, defining the structure and operations for the list.

	- monitor.h: Header file for the monitor implementation. It includes the definitions for the monitor, thread types, and synchronization functions.

	- readwrite.h: Header file for reader and writer functions. It defines the operations for reading and writing to the shared resource.
	- respective .c files including implementation of headers

- tests/:

	- testlist.c: Test file for the linked list implementation.
	- monitortest.c: Test file for the integrated components, particularly the reader-writer problem using the monitor.
- Makefile: Used to compile and run tests. Contains commands make test for running list tests and make test_monitor for testing the reader-writer problem.

### How It Works
1. Linked List: The linked list is used to manage queues of threads waiting to access the shared resource. The list operations allow for adding, removing, and searching elements in the list.

2. Monitor: The monitor uses mutex locks and condition variables to manage access to the shared resource. It ensures that multiple readers can access the resource simultaneously or provide exclusive access to a writer.

3. Reader and Writer Threads: These threads simulate the actions of reading from and writing to the shared resource. They interact with the monitor to ensure synchronized access.

4. Testing: The project includes tests for both the linked list and the integrated reader-writer solution. These tests validate the functionality and synchronization logic.

## Usage
Run the tests to validate the implementation:

- To test the linked list: make test
- To test the reader-writer problem: make test_monitor