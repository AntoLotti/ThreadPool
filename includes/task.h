#ifndef TASK_H
#define TASK_H

//========INCLUDES========//
#include <common.h>
#include <task.h> 

//========DEFINES=========//
#define MAX_RAND_NUM    10

//========TYPES===========//
typedef struct task_s
{
    void* (*taskAction)( void* arg );   //Pointer to a function that return a void pointer and recive a void pointer as argument
    void* arg;                          //Pointer to the arguments of the functions
}task_t;

//====FUN DECLARATIONS===//
void* tasksAcction_f( void* arg );

task_t taskGenerator_f();




#endif