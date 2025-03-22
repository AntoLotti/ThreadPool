//========INCLUDES========//
#include <common.h>
#include <task.h> 

//========FUN DEF=========//
void* example_task(void* arg) 
{
    int num = *(int*)arg;
    free(arg);
    printf("Processing task %d\n", num);
    sleep(2);  // Simulate task work
    return NULL;
}