//========INCLUDES========//
#include <common.h>
#include <threadPool.h>

//include the tasks
#include <task.h>
//========TH CONTROL======//


//========FUN DEF=========//


//========MAIN============//
int main( int argc, char* argv[] )
{
    threadPool_t thpool;   
    threadpoolInit_f( &thpool );

    //Creating the tasks
    for (int i = 0; i < MAX_TASKS; i++) {
        int* task_num = malloc(sizeof(int));
        *task_num = i;
        addTaskToQueue(&thpool, task_num, example_task );
    }
    
    sleep(15);

    threadpoolDestroy_f( &thpool );

    return 0; 
}