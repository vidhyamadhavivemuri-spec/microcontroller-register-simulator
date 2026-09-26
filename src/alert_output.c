#include "alert_output.h"

static int alert_output_state = 0;

void alert_output_init(void)
{
    alert_output_state = 0;
}

void alert_output_on(void)
{
    alert_output_state = 1;
}

void alert_output_off(void)
{
    alert_output_state = 0;
}

int alert_output_is_on(void)
{
    return alert_output_state;
}
