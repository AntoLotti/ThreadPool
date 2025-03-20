//========INCLUDES========//
#include <common.h>
#include <threadPool.h>


//========FUN DEF=========//
static bool threadsCreation_f( threadPool_t* src )
{
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if ( pthread_create( src->threadsArray[ i ], NULL, &threadpoolTaskAssigner_f, src ) != 0  )
        {
            perror("Error creating the threads");
            return false;
        }
    }

    return true;
}

static bool threadsDestruction_f( threadPool_t* src )
{
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if ( pthread_join( src->threadsArray[ i ], NULL ) != 0  )
        {
            perror("Error joining the threads");
            return false;
        }
    }

    return true;
}

void threadpoolInit_f( threadPool_t* src )
{
    pthread_mutex_init( &(src->lock), NULL );   //Initialization of the mutex
    pthread_cond_init( &(src->notify), NULL );  //Initialization of the condition variable

    threadsCreation_f( src );         //Creation of the threads

    src->nqueued    = 0;        // Initialization of the index
    src->queue_top  = 0;        // Initialization of the index 
    src->queue_last = 0;        // Initialization of the index
    src->stop       = false;    // Initialization of the index 

}

void threadpoolDestroy_f( threadPool_t* src )
{
    pthread_mutex_lock( &(src->lock) );         // Make sure that only one thread access this function
    src->stop = true;                           // Ensured the condition
    pthread_cond_broadcast( &(src->notify) );   // Ensure that all the threads get the notification
    pthread_mutex_unlock( &(src->lock) );       // Release the mutex
    
    threadsDestruction_f( src );                //Join the threads

    pthread_mutex_destroy( &(src->lock) );      // Destroy the mutex
    pthread_cond_destroy( &(src->notify) );     // Destroy the condition variable

}

void* threadpoolTaskAssigner_f( void* src )
{
    threadPool_t* thpool = (threadPool_t*)src ;

    while ( 1 )
    {
        // Lock the mutex so only one thread can modify the queue
        pthread_mutex_lock( &(thpool->lock) );
        
        // Check if the Queue is empty, if it's wait untile there are some task
        while ( thpool->nqueued == 0 && !(thpool->stop) )
        {
            pthread_cond_wait( &(thpool->notify), &(thpool->lock) );
        }

        // Check if the threadpool must stop
        if ( thpool->stop == true )
        {
            pthread_mutex_unlock( &(thpool->lock) );
            pthread_exit( &(thpool->lock) );   
            //return NULL;
        }
        
        // Assigne a task 
        task_t taskTh = {
            .taskAction = NULL,
            .arg        = NULL,
        };
        taskTh = thpool->taskQueue[ thpool->queue_top ];

        // Move the task in the queue (Circular Queues)
        thpool->queue_top = (thpool->queue_top + 1) % MAX_TASKS;
        thpool->nqueued--;

        // Free the mutex
        pthread_mutex_unlock( &(thpool->lock) );

        // Ejecute the task
        (*(taskTh.taskAction))( taskTh.arg );
    }
    
    return NULL;
}