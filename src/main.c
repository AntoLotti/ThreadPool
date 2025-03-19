//========INCLUDES========//
#include <common.h>
#include <threadPool.h>

//========TH CONTROL======//
pthread_t pthreadArray[MAX_THREADS];

pthread_mutex_t mutexQueue_mtx;

//========FUN DEF=========//
static void TaskQueueInit_f( int num )
{
    for (int i = 0; i < num; i++)
    {
        addTaskToQueue_f( num, taskGenerator_f() );
    }
}

static bool threadsCreation_f( threadPool_t src )
{
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if ( pthread_create( &pthreadArray[ i ], NULL, &threadPoolTaskAssigner_f, &src ) != 0  )
        {
            return false;
        }
    }

    return true;
}

static bool threadsDestruction_f()
{
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if ( pthread_join( pthreadArray[ i ], NULL ) != 0  )
        {
            return false;
        }
    }

    return true;
}

//========MAIN============//
int main( int argc, char* argv[] )
{
    pthread_mutex_init( &mutexQueue_mtx, NULL );

    TaskQueueInit_f( MAX_TASKS );

    threadPool_t arg = 
    {
        .others = NULL,
        .mux = &mutexQueue_mtx,
    };
    
    if ( !threadsCreation_f( arg ) )
    {
        perror( "Error in the creation of the Threads" );
        return -1;
    }
    
    if ( !threadsDestruction_f() )
    {
        perror( "Error in the join of the Threads" );
        return -1;
    }

    pthread_mutex_destroy( &mutexQueue_mtx );

    return 0; 
}