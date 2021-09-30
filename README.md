# Overview

In this project, we will create a thread-safe version of an existing list library. We will then test it using a provided solution to the producers-consumers problem.

You will create the ThreadsafeBoundedList.c file in the wrapper-library subfolder to complete the implementation of the thread-safe list library.

## Specification

Wrap an existing library

First, we will create a monitor version (a monitor consists of a lock and one or more condition variables) of a doubly linked list library implementation (that is provided for you in the list folder). We will also add an additional feature to bound the capacity of the list. Since we don't have the source code for the list library, we will build a wrapper library that creates the monitor version around the original library. 

The API for this library has been provided to you in the ThreadsafeBoundedList.h file in wrapper-library folder.

We declare a structure that contains a pointer to the underlying list as well as additional variables to implement the monitor. However, we declare it incomplete in ThreadsafeBoundedList.h header file as shown below.

```c
struct tsb_list;
```

We will provide a complete declaration in ThreadsafeBoundedList.c file as shown below. This makes the internals of the structure opaque to the users and they cannot directly modify those variables.

```c
struct tsb_list {
 struct list *list;
 int capacity;
 Boolean stop_requested;
 pthread_mutex_t mutex;
 pthread_cond_t listNotFull;
 pthread_cond_t listNotEmpty;
};
```
We also provide wrapped versions of all the underlying functions from the list library as well as some additional functions. See the header file for details on the functions that you are wrapping. You will be creating and implementing these functions in the ThreadsafeBoundedList.c file. Each function should be protected by a mutex. If the list becomes full, then adding to the list shall block on a condition variable. If the list is empty, then removing from the list shall block on another condition variable.

Relevant man pages are: 
- pthread_mutex_init
- pthread_mutex_lock
- pthread_mutex_unlock
- pthread_cond_init
- pthread_cond_wait
- pthread_cond_signal
- pthread_cond_broadcast
- pthread_cond_destroy

## Using the wrapper Library

We will simulate a size-bounded queue (implemented as a doubly-linked list with a limit on maximum size) being shared by multiple producers and multiple consumers running simultaneously. Suppose we have m producers and n consumers (where m and n are supplied as command line arguments).  The initial main process creates a global queue data structure so all threads can access it.  Then the main process creates m producer threads and n consumer threads.

We will fix the number of items each producer produces (as a command line argument). Then we will keep track of how many items each consumer actually consumed. At the end of the program, we print out the total number of items produced versus the total number of items consumed. These two numbers should be the same unless the program has race conditions.

The items are a structure that contain an unique id (basically number the items 1, 2, 3, ... as they are entered in the queue) and also contains the index of the producer that created it.

We have provided you with a working version of the producer-consumer test program in the file pc.c. You should not modify the test program pc.c. However, you will need to add an additional function finishUp() to your wrapper list class that allows the simulation to be stopped after the producers are done by signaling the consumers to clean up any remaining items in the queue.

The producer/consumer threads test program uses the monitor version of the doubly linked list to run the simulation.  To test your monitor version, the producers randomly insert new items at the front or back of the queue.  Similarly the consumers randomly remove items from the front or back of the queue.

## Setup for libraries
We are using two libraries in this project. The original linked list library libmylist.so  that is in the folder ./list/lib and the wrapper library libthreadsafe-mylib.so that is in the ./lib directory. You must export both paths in LD_LIBRARY_PATH for everything to work and the paths must be relative to the executable (pc).  For example, use the following command before running the pc executable:

  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./list/lib:./lib

## Notes on testing
When testing your program limit the number of threads to less that ten and number of items produced per producer to less than ten thousand to avoid overloading onyx. On your system, you can test with higher values.

Run the program several times for the same input arguments. Verify that the results do not vary. Comment out the output statements. See if that changes the results for the number of items consumed or produced.

Use the testing script test-pc.sh provided in the assignment folder. 

## Extra requirements (for Graduate Students only)
Create another version of the testing program pc.c and call it pc-mq.c and adjust the Makefile accordingly.

Add another command line argument that allows the user to specify the number of queues (with the same size limit on each). The number of queues should be the first command line argument.

Usage: pc-mq <#queues> <poolsize> <#items/producer> <#producers> <#consumers> <sleep interval(microsecs)
                                                                                     
Now modify your the testing code to create multiple queues and have the producers/consumers access the queues in a round-robin fashion, which is explained below.
Suppose we have k queues. Then if the ith queue is full, the producer moves on to the (i+1) mod kth queue. Similarly if the ith queue is empty, the consumer moves on to the (i + 1) mod kth queue.

Testing would be the same as before. An additional test script is test-pc-mq.sh. You could also informally test if multiple queues allows the producers and consumers to get their work done faster although that would depend on the mix of the work being simulated.

## Due Date:  

23:59pm, October 19th, 2021. 10% of penalty for late submission within 48 hours; 20% of penalty after the 48 hours window.

## Grading Rubric (for Undergraduate students)

All grading will be executed on onyx.boisestate.edu. Submissions that fail to compile will not being graded.
                                                                                     
- [10 pts] Compiling
  - Each compiler warning will result in a 3 point deduction.
  - You are not allowed to suppress warnings
- [10 pts] Code quality
  - [5 pts] Code is formatted correctly and follows a consistent style
  - [5 pts] Code is commented when necessary
- [70 pts] Functional Requirements: single queue monitor
- [10 pts] Documentation: README.md file (replace this current README.md with a new one using the template on the course page)

Note: Running valgrind is not required anymore for this and the next 2 projects.
                                                                                     
 ## Grading Rubric (for Graduate students)

All grading will be executed on onyx.boisestate.edu. Submissions that fail to compile will not being graded.
                                                                                     
- [10 pts] Compiling
  - Each compiler warning will result in a 3 point deduction.
  - You are not allowed to suppress warnings
- [10 pts] Code quality
  - [5 pts] Code is formatted correctly and follows a consistent style
  - [5 pts] Code is commented when necessary
- [40 pts] Functional Requirements: single queue monitor
- [30 pts] Functional Requirements: multiple queue monitor                                                                      
- [10 pts] Documentation: README.md file (replace this current README.md with a new one using the template on the course page)
                                                                                     
Note: Running valgrind is not required anymore for this and the next 2 projects.
