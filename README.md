Overview

In this project, we will create a thread-safe version of an existing list library. We will then test it using a provided solution to the producers-consumers problem.

The starter code looks like the listing below:

[jxiao@cs p3]$ ls -A
backpack.sh  include  Item.c  Item.h  lib  Makefile  p3-rubric.txt  pc.c  test-pc.sh  wrapper-library
[jxiao@cs p3]$ ls -A lib include wrapper-library
include:
.gitkeep

lib:
.gitkeep

wrapper-library:
Makefile  ThreadsafeBoundedList.h

You will create the ThreadsafeBoundedList.c file in the wrapper-library subfolder to complete the implementation of the thread-safe list library.

Specification
Wrap an existing library

First, we will create a monitor version of a doubly linked list library implementation (that is provided for you in the list folder). We will also add an additional feature to bound the capacity of the list. Since we don't have the source code for the list library, we will build a wrapper library that creates the monitor version around the original library. 

The API for this library has been provided to you in your backpack repo in the ThreadsafeBoundedList.h file in wrapper-library folder.

We declare a structure that contains a pointer to the underlying list as well as additional variables to implement the monitor. However, we declare it incomplete in ThreadsafeBoundedList.h header file as shown below.

struct tsb_list;

We will provide a complete declaration in ThreadsafeBoundedList.c file as shown below. This makes the internals of the structure opaque to the users and they cannot directly modify those variables.

struct tsb_list {
struct list *list;
int capacity;
Boolean stop_requested;
pthread_mutex_t mutex;
pthread_cond_t listNotFull;
pthread_cond_t listNotEmpty;
};


We also provide wrapped versions of all the underlying functions from the list library as well as some additional functions. See the header file for details on the functions that you are wrapping. You will be creating and implementing these functions in the ThreadsafeBoundedList.c file. Each function should be protected by a mutex. If the list becomes full, then adding to the list shall block on a condition variable. If the list is empty, then removing from the list shall block on another condition variable.

Relevant man pages are: 
pthread_mutex_init
pthread_mutex_lock
pthread_mutex_unlock
pthread_cond_init
pthread_cond_wait
pthread_cond_signal
pthread_cond_broadcast
pthread_cond_destroy

Using the wrapper Library

We will simulate a size-bounded queue (implemented as a doubly-linked list with a limit on maximum size) being shared by multiple producers and multiple consumers running simultaneously. Suppose we have m producers and n consumers (where m and n are supplied as command line arguments).  The initial main process creates a global queue data structure so all threads can access it.  Then the main process creates m producer threads and n consumer threads.

We will fix the number of items each producer produces (as a command line argument). Then we will keep track of how many items each consumer actually consumed. At the end of the program, we print out the total number of items produced versus the total number of items consumed. These two numbers should be the same unless the program has race conditions.

The items are a structure that contain an unique id (basically number the items 1, 2, 3, ... as they are entered in the queue) and also contains the index of the producer that created it.

We have provided you with a working version of the producer-consumer test program in the file pc.c. You should not modify the test program pc.c. However, you will need to add an additional function finishUp() to your wrapper list class that allows the simulation to be stopped after the producers are done by signaling the consumers to clean up any remaining items in the queue.

The producer/consumer threads test program uses the monitor version of the doubly linked list to run the simulation.  To test your monitor version, the producers randomly insert new items at the front or back of the queue.  Similarly the consumers randomly remove items from the front or back of the queue.

Setup for libraries
We are using two libraries in this project. The original linked list library libmylist.so  that is in the folder ../list/lib (relative to p3) and the wrapper library  libthreadsafe-mylib.so  that is in the ./lib directory (relative to p3). You must export both paths in LD_LIBRARY_PATH for everything to work and the paths must be relative to the executable (pc).  For example, use the following command before running the pc executable:

  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../list/lib:./lib

Notes on testing
When testing your program limit the number of threads to less that ten and number of items produced per producer to less than ten thousand to avoid overloading onyx. On your system, you can test with higher values.
Run the program several times for the same input arguments. Verify that the results do not vary.
Comment out the output statements. See if that changes the results for the number of items consumed or produced.
Use the testing script backpack.sh provided in the assignment folder. It uses the test-pc.sh script, which has also been provided.

Submission
Projects must be submitted by 23:59pm of the due date for full credit. Projects can be turned in up to 48 hours late without pre-approval from the instructor for a 10% penalty.  Any check-in activities to your backpack repository occur after the due date, but are within the 48 hours window, would cause the entire project to be considered as a late submission, and thus would incur a 10% penalty. Submission after the 48 hours window will not be graded.

Due Date:  March 3rd, 2020.

Grading Rubric

[10 pts]  Compiling
  Each compiler warning will result in a 3 point deduction.
  You are not allowed to suppress warnings
[80 pts]  Functional Requirements: single queue monitor
[10 pts]	Documentation: README.md file
