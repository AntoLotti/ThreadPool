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
    void* others;
    pthread_mutex_t* mux;
}threadPool_t;


//====FUN DECLARATIONS===//
void* executeTaskFun_f( task_t task );

void addTaskToQueue_f( int pos, task_t task);

void shiftElementsTaskQueue_f();

void* threadPoolTaskAssigner_f( void* src );

#endif