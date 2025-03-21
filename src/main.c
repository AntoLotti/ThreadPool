//========INCLUDES========//
#include <common.h>
#include <threadPool.h>

//========TH CONTROL======//


//========FUN DEF=========//


//========MAIN============//
int main( int argc, char* argv[] )
{
    threadPool_t thpool;   
    threadpoolInit_f( &thpool );

    for (size_t i = 0; i < 5; i++)
    {
        task_t task = taskGenerator_f();
        addTaskToQueue( &thpool, task.arg, task.taskAction );
    }
    
    sleep(5);

    threadpoolDestroy_f( &thpool );

    return 0; 
}