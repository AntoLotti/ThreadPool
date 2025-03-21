//========INCLUDES========//
#include <common.h>
#include <task.h> 

//========FUN DEF=========//
void* tasksAcction_f( void* arg )
{
    int num = *(int*)arg;
    printf( "\n\t > the number is: %d ", num );
    sleep(1);
    free(arg);
    return NULL;
}

task_t taskGenerator_f()
{
    int* num_p = malloc( sizeof(int) );
    *num_p = ( rand() % 5 );

    task_t t ={
        .arg = num_p,
        .taskAction = &(tasksAcction_f),
    };
    
    return t;
}