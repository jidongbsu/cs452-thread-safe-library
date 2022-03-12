#include <stdio.h>
#include <stdlib.h>
#include "ThreadsafeBoundedList.h"

/* Contains functions to manipulate a thread-safe bounded doubly-linked list.  */

struct tsb_list {
    struct list *list;
    int capacity;
    int stop_requested;
    pthread_mutex_t mutex;
    pthread_cond_t listNotFull;
    pthread_cond_t listNotEmpty;
};

/* write all your functions below */
