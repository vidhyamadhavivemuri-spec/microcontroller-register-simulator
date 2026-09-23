#include <assert.h>
#include <stdio.h>

#include "interrupt.h"
#include "register.h"

static int handler_called = 0;

void test_int0_handler(void)
{
    handler_called++;
}
void test_int1_handler(void)
{
    handler_called++;
}
void test_handler_registration(void)
{
    interrupt_init();

    /* Register a handler for INT0. */
    interrupt_register_handler(0, test_int0_handler);

    /* Enable and trigger INT0. */
    interrupt_int0_enable();
    interrupt_int0_trigger();

    assert(INT_PENDING == 1);

    /* Service INT0. */
    assert(interrupt_service_int0() == true);
    assert(handler_called == 1);
    /* INT0 should be cleared. */
    assert(INT_PENDING == 0);
}
void test_int1_handler_registration(void)
{
    interrupt_init();

    handler_called = 0;

    interrupt_register_handler(1, test_int1_handler);

    interrupt_int1_enable();
    interrupt_int1_trigger();

    assert(INT_PENDING == 2);

    assert(interrupt_service_int1() == true);

    assert(INT_PENDING == 0);
    assert(handler_called == 1);
}
void test_interrupt_priority_with_handlers(void)
{
    interrupt_init();

    handler_called = 0;

    interrupt_register_handler(0, test_int0_handler);
    interrupt_register_handler(1, test_int1_handler);

    interrupt_int0_enable();
    interrupt_int1_enable();

    interrupt_int0_trigger();
    interrupt_int1_trigger();

    assert(INT_PENDING == 3);

    /* INT0 has higher priority. */
    assert(interrupt_service_next() == true);
    assert(handler_called == 1);
    assert(INT_PENDING == 2);

    /* INT1 should now be serviced. */
    assert(interrupt_service_next() == true);
    assert(handler_called == 2);
    assert(INT_PENDING == 0);
}

int main(void)
{
    test_handler_registration();
    test_int1_handler_registration();
    test_interrupt_priority_with_handlers();
    
    printf("Interrupt handler registration test passed!\n");

    return 0;
}