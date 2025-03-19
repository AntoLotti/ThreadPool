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

    src->nqueued    = 0;    // Initialization of the index
    src->queue_top  = 0;    // Initialization of the index 
    src->queue_last = 0;    // Initialization of the index
    src->stop       = 0;    // Initialization of the index 

}

void threadpoolDestroy_f( threadPool_t* src )
{
    pthread_mutex_destroy( &(src->lock) );      // Destroy the mutex
    pthread_cond_destroy( &(src->notify) );     // Destroy the condition variable

    threadpoolDestroy_f( src );     //Join the threads
}

void* threadpoolTaskAssigner_f( void* src )
{

}