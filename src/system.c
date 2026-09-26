#include "system.h"

static system_state_t system_state = SYSTEM_INIT;

void system_init(void)
{
    system_state = SYSTEM_INIT;
}

system_state_t system_get_state(void)
{
    return system_state;
}

void system_update(void)
{
    if (system_state == SYSTEM_INIT)
    {
        system_state = SYSTEM_RUNNING;
    }
}

void system_set_alert(void)
{
    system_state = SYSTEM_ALERT;
}

void system_clear_alert(void)
{
    system_state = SYSTEM_RUNNING;
}
