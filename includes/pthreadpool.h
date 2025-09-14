#ifndef PTHREADPOOL_H
#define PTHREADPOOL_H

//========INCLUDES========//
//Standars
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Threads
#include <pthread.h>
#include <unistd.h>
//Errors
#include <errno.h>

//========DEFINES=========//
#define MAX_THREADS     5
#define MAX_TASKS       40

//========TYPES===========//
typedef struct task_s
{
    void  (*fn)(void* arg);     //Pointer to a function that recive a void pointer as argument
    void* arg;                  //Pointer to the arguments of the functions
}task_t;

typedef struct pthreadpool_s
{
    pthread_t       threads[MAX_THREADS];   // An array of initialized threads 
    pthread_mutex_t lock;                   // A mutex to synchronize access to the task queue. Ensures that only one thread at a time modifies the queue.
    pthread_cond_t  notify;                 // A condition variable used to notify worker threads when new tasks are available.
    task_t  task_queue[MAX_THREADS];        // A circular queue that store the new tasks
    int     queue;                          // The number of tasks currently in the queue.
    int     queue_front;                    // A index of the task queue, that point to the first elemment to use of the queue
    int     queue_back;                     // A index of the task queue, that point to the next availabe space
    int     stop;                           // A flag to indicate if the pool should stop executing (used for shutdown; true to stop ).
}pthreadpool_t;


//====FUN DECLARATIONS===//
/**
 * @brief pthreadpool_init
 * @details function to initialice a pthreadpool
 * @author Antonio Lotti 
 * @date 04/09/2025
 * @param src pointer to a pthreadpool_t structure
 * @return return 0 on success and a non-zero error code on error.
 */
void pthreadpool_init( pthreadpool_t *src );

/**
 * @brief pthreadpool_destroy
 * @details function to destroy a pthreadpool structure
 * @author Antonio Lotti 
 * @date 04/09/2025
 * @param src pointer to a pthreadpool_t structure
 * @return nothing
 */
void pthreadpool_destroy( pthreadpool_t *src );

/**
 * @brief pthreadpool_add_task
 * @details function to add a task to the queue of the pthreadpool
 * @author Antonio Lotti 
 * @date 04/039/2025
 * @param dst pointer to a pthreadpool_t structure
 * @param arg void pointer to the arguments of the task
 * @param fun pointer to the task function
 * @return nothing
 */
void pthreadpool_add_task( pthreadpool_t *dst, void *(*fun)( void *arg ), void *arg );

/**
 * @brief pthreadpool_function
 * @details This is function that will be runing in each thread
 * @author Antonio Lotti
 * @date 13/04/2025
 * @param src A void pointer to a pthreadpool type
 */
void* pthreadpool_function(void* src);

#endif