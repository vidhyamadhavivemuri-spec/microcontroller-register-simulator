#include <assert.h>
#include <stdio.h>

#include "system.h"

void test_system_state_transition(void)
{
    system_init();

    assert(system_get_state() == SYSTEM_INIT);

    system_update();

    assert(system_get_state() == SYSTEM_RUNNING);

    system_set_alert();

    assert(system_get_state() == SYSTEM_ALERT);

    system_clear_alert();

    assert(system_get_state() == SYSTEM_RUNNING);
}

int main(void)
{
    test_system_state_transition();

    printf("System state tests passed!\n");

    return 0;
}