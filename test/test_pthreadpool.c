//========INCLUDES========//
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h> 
#include <cmocka.h>

#include <pthreadpool.h>

//======= FIXTURES =======//
static int setup( void **state )
{
    (void)*state;
    return 0;
}

static int teardown( void **state )
{
    (void)*state;
    return 0;
}

//========= TESTS ========//

void test_pthreadpool_init_initializesAllFieldsCorrectly( void **state ) 
{
    //Arrange
    (void)*state;
    pthreadpool_t threadpool;

    //Act
    int result = pthreadpool_init( &threadpool );

    //Assert
    assert_int_equal( threadpool.numTasks, 0 );
    assert_int_equal( threadpool.queue_top, 0 );
    assert_int_equal( threadpool.queue_last, 0 );
    assert_int_equal( ( threadpool.stop == false ? 0 : 1 ), 0 );
    assert_int_equal( result, 0 );
}



//========= MAIN =========//
int main(void) 
{
    const struct CMUnitTest tests[] = 
    {
        cmocka_unit_test(test_pthreadpool_init_initializesAllFieldsCorrectly),
    };

    return cmocka_run_group_tests( tests, setup, teardown );
}