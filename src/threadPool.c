//========INCLUDES========//
#include <common.h>
#include <threadPool.h>

//========GLOBALS???======//
task_t taskQueue[MAX_TASKS];

//========FUN DEF=========//
void* executeTaskFun_f( task_t task )
{
    return task.taskAction( task.arg );
}

void addTaskToQueue_f( int pos, task_t task )
{
    taskQueue[pos] = task;
}

void shiftElementsTaskQueue_f()
{
    for (int i = MAX_TASKS; i > 0; i--)
    {   
        taskQueue[( i - 1 )] = taskQueue[i];    
    }
}

void* threadPoolTaskAssigner_f( void* src )
{

    pthread_mutex_t *mux = (*(threadPool_t*)src).mux;

    while (1)
    {
        task_t taskThread;
        
        //Take Task Of The Queue
        pthread_mutex_lock(mux);

        taskThread = taskQueue[0];
        shiftElementsTaskQueue_f();

        pthread_mutex_unlock(mux);

        if ( taskExist_f( taskThread ) )
        {
            executeTaskFun_f( taskThread );
        }
    }

    return NULL;
}