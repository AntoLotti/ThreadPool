//========INCLUDES========//
#include <common.h>
#include <task.h> 

//========FUN DEF=========//
bool taskExist_f( task_t task )
{
    return ( !(task.arg == NULL && task.taskAction == NULL) );
}

void* tasksAcction_f( void* arg )
{
    sleep(5);
    parameters_t param = *(parameters_t*)arg;
    //free(arg);
    printf("\n > The argument A of the task is: %d \n", param.argA );
    printf("> The argument B of the task is: %d \n", param.argB );
    printf("> The sum of the tow arguments is: %d", param.argA + param.argB );
    
    return NULL;
}

task_t taskGenerator_f()
{
    parameters_t arg = {
        .argA = 0,
        .argB = 0,
    };
    
    arg.argA = rand()%MAX_RAND_NUM;
    arg.argB = rand()%MAX_RAND_NUM;
    
    /*parameters_t *param = malloc( sizeof(parameters_t) ); 
    *param = arg;*/

    parameters_t *param = &arg;
    
    task_t t = {
        .taskAction = &tasksAcction_f,
        .arg = param,
    };
    
    return t;
}