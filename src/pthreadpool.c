//========INCLUDES========//
#include <pthreadpool.h>

//========FUN DEC=========//
static bool creator_pthreads( pthreadpool_t *src );
static bool destructor_pthreads( pthreadpool_t *src );

//========FUN DEF=========//
void pthreadpool_init( pthreadpool_t* src )
{
    
}

void pthreadpool_add_task( pthreadpool_t *dst, void *(*fun)( void *arg ), void *arg )
{

}

void pthreadpool_destroy( pthreadpool_t *src )
{

}

void* pthreadpool_assigner( void *src )
{

}