#ifndef THREADPOOL_H
#define THREADPOOL_H

//========INCLUDES========//
#include <common.h>

//========DEFINES=========//
#define MAX_THREADS     5
#define MAX_TASKS       40

//========TYPES===========//
typedef enum thpool_error_e
{
    PROBLEM_NA              = 0,
    
    PROBLEM_EAGAIN          = 1,    //Insufficient   resources  to  create  anothe thread.
    PROBLEM_EINVAL          = 2,    //Invalid settings in attr.
    PROBLEM_EPERM           = 3,    //No  permission  to  set the scheduling policy and parameters specified in attr.
    PROBLEM_MX_EAGAIN       = 4,
    PROBLEM_MX_EINVAL       = 5,    //The  mutex  has not been properly initialized.
    PROBLEM_MX_EPERM        = 6,
    PROBLEM_MX_ENOMEM       = 7,
    PROBLEM_MX_EBUSY        = 8,    //The mutex has already been initialized and is in use.
    PROBLEM_JOIN_EDEADLK    = 9,    //A  deadlock  was  detected or  thread specifies the calling thread.
    PROBLEM_JOIN_EINVAL     = 10,   //thread is not a joinable thread.
    PROBLEM_JOIN_EINVAL     = 11,   //Another  thread  is  already  waiting to join with this thread.
    PROBLEM_JOIN_ESRCH      = 12,   //No thread with the ID thread could be found.
    
    PROBLEM_UNEXPECTED  = 99,
} thpool_error_t;

typedef struct task_s
{
    void* (*taskAction)( void* arg );       //Pointer to a function that return a void pointer and recive a void pointer as argument
    void* arg;                              //Pointer to the arguments of the functions
}task_t;

typedef struct threadPool_s
{
    pthread_mutex_t lock;                   // A mutex to synchronize access to the task queue. Ensures that only one thread at a time modifies the queue.
    pthread_cond_t  notify;                 // A condition variable used to notify worker threads when new tasks are available.
    pthread_t   threadsArray[MAX_THREADS];  //
    task_t      taskQueue[MAX_TASKS];       //
    int         numTasks;                   // The number of tasks currently in the queue.
    int         queue_top;                  // The index of the first task in the queue.
    int         queue_last;                 // The index of the last task in the queue.
    bool        stop;                       // A flag to indicate if the pool should stop executing (used for shutdown; true to stop ).
}threadPool_t;


//====FUN DECLARATIONS===//
thpool_error_t pthreadpool_init( threadPool_t* src );

void pthreadpool_add_task( threadPool_t* dst, void* arg, void* (*fun)( void* arg ) );

void pthreadpool_destroy( threadPool_t* src );

void* pthreadpool_assigner( void* src );

#endif