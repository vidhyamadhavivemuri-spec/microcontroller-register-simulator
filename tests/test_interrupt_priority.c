#include <assert.h>
#include <stdio.h>

#include "interrupt.h"
#include "register.h"

void test_interrupt_priority(void)
{
    /* Reset interrupt controller. */
    interrupt_init();

    /* Enable INT0 and INT1. */
    interrupt_int0_enable();
    interrupt_int1_enable();

    /* Trigger both interrupts. */
    interrupt_int0_trigger();
    interrupt_int1_trigger();

    /* Verify INT0 is selected first. */
    assert(INT_PENDING == 3);
    assert(interrupt_get_pending() == 0);

    /* Service INT0. */
    interrupt_service_int0();

    /* Verify INT0 cleared and INT1 still pending. */
    assert(INT_PENDING == 2);
    assert(interrupt_get_pending() == 1);

    /* Service INT1. */
    interrupt_service_int1();

    /* Verify both interrupts are cleared. */
    assert(INT_PENDING == 0);
}
void test_single_int1_service(void)
{
    interrupt_init();

    interrupt_int1_enable();
    interrupt_int1_trigger();

    assert(INT_PENDING == 2);
    assert(interrupt_get_pending() == 1);

    assert(interrupt_service_next() == true);

    assert(INT_PENDING == 0);
}

int main(void)
{
    test_interrupt_priority();
    test_single_int1_service();

    printf("Interrupt controller integration tests passed!\n");

    return 0;
}
