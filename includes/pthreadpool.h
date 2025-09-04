#ifndef PTHREADPOOL_H
#define PTHREADPOOL_H

//========INCLUDES========//
//Standars
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Threads
#include <pthread.h>
#include <unistd.h>
//Errors
#include <errno.h>

//========DEFINES=========//
#define MAX_THREADS     5
#define MAX_TASKS       40

//========TYPES===========//
typedef struct task_s
{
    void *(*task_action)( void* arg );      //Pointer to a function that return a void pointer and recive a void pointer as argument
    void *arg;                              //Pointer to the arguments of the functions
}task_t;

typedef struct pthreadpool_s
{
#ifdef DEBUG
    int         thread_id;                  //Id of the thread
#endif
}pthreadpool_t;


//====FUN DECLARATIONS===//
/**
 * @brief pthreadpool_init
 * @details function to initialice a threadpool
 * @author Antonio Lotti 
 * @date 04/09/2025
 * @param src pointer to a pthreadpool_t structure
 * @return return 0 on success and a non-zero error code on error.
 */
void pthreadpool_init( pthreadpool_t *src );

/**
 * @brief pthreadpool_add_task
 * @details function to add a task to the queue of the threadpool
 * @author Antonio Lotti 
 * @date 04/039/2025
 * @param dst pointer to a pthreadpool_t structure
 * @param arg void pointer to the arguments of the task
 * @param fun pointer to the task function
 * @return nothing
 */
void pthreadpool_add_task( pthreadpool_t *dst, void *(*fun)( void *arg ), void *arg );

/**
 * @brief pthreadpool_destroy
 * @details function to destroy a threadpool structure
 * @author Antonio Lotti 
 * @date 04/09/2025
 * @param src pointer to a pthreadpool_t structure
 * @return nothing
 */
void pthreadpool_destroy( pthreadpool_t *src );

/**
 * @brief pthreadpool_assigner
 * @details function to assigne task to the threads 
 * @author Antonio Lotti
 * @date 04/09/2025
 * @param src pointer to the pthreadpool_t
 * @return nothing
 */
void* pthreadpool_assigner( void *src );

#endif