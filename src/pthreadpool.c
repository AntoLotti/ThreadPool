//========INCLUDES========//
#include <pthreadpool.h>

//========FUN DEC=========//
static bool creator_pthreads( pthreadpool_t* src );
static bool destructor_pthreads( pthreadpool_t *src );

//========FUN DEF=========//
static bool creator_pthreads( pthreadpool_t* src )
{
    for (size_t i = 0; i < MAX_THREADS; i++)
    {
        if (pthread_create(src->threads[i], NULL, pthreadpool_function, src ) != 0 )
        {
            return false;
        }
    }
    return true;
}

//static bool destructor_pthreads( pthreadpool_t *src );


void pthreadpool_init( pthreadpool_t* src )
{
    if( src == NULL )
    {
        //TODO: Add error handler
        return;
    }

    src->queue          = 0;
    src->queue_front    = -1;
    src->queue_back     = -1;
    src->stop           = false;

    pthread_mutex_init( &(src->lock), NULL);  
    pthread_cond_init( &(src->notify), NULL);
    
    for (size_t i = 0; i < MAX_TASKS; i++)
    {
        src->task_queue[i].fn   = NULL;
        src->task_queue[i].arg  = NULL;
    }
    
    if (!creator_pthreads(src))
    {
        //TODO: create a error handler
        return;
    }
    
}

void pthreadpool_destroy( pthreadpool_t *src )
{

}


void pthreadpool_add_task( pthreadpool_t* dst, void* (*fun)(void*), void* arg)
{

}

void* pthreadpool_function(void* src)
{

}