#ifndef THREADPOOL_H
#define THREADPOOL_H

//========INCLUDES========//
#include <common.h>
#include <task.h> 

//========DEFINES=========//
#define MAX_THREADS     5
#define MAX_TASKS       40

//========TYPES===========//
typedef struct threadPool_s
{
    pthread_mutex_t lock;                   // A mutex to synchronize access to the task queue. Ensures that only one thread at a time modifies the queue.
    pthread_cond_t  notify;                 // A condition variable used to notify worker threads when new tasks are available.
    pthread_t   threadsArray[MAX_THREADS];  //
    task_t      taskQueue[MAX_TASKS];       //
    int         nqueued;                    // The number of tasks currently in the queue.
    int         queue_top;                  // The index of the first task in the queue.
    int         queue_last;                 // The index of the last task in the queue.
    bool        stop;                       // A flag to indicate if the pool should stop executing (used for shutdown; true to stop ).
}threadPool_t;


//====FUN DECLARATIONS===//
void threadpoolInit_f( threadPool_t* src );

void threadpoolDestroy_f( threadPool_t* src );

void* threadpoolTaskAssigner_f( void* src );

void addTaskToQueue( threadPool_t* dst, task_t src );

#endif