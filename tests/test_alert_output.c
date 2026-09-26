#include <assert.h>
#include <stdio.h>

#include "alert_output.h"

void test_alert_output(void)
{
    /* Initialize output */
    alert_output_init();

    assert(alert_output_is_on() == 0);

    /* Turn output ON */
    alert_output_on();

    assert(alert_output_is_on() == 1);

    /* Turn output OFF */
    alert_output_off();

    assert(alert_output_is_on() == 0);
}

int main(void)
{
    test_alert_output();

    printf("Alert output tests passed!\n");

    return 0;
}
