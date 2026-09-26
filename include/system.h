#ifndef SYSTEM_H
#define SYSTEM_H

typedef enum
{
    SYSTEM_INIT,
    SYSTEM_RUNNING,
    SYSTEM_ALERT
} system_state_t;

void system_init(void);

system_state_t system_get_state(void);

void system_update(void);

void system_set_alert(void);

void system_clear_alert(void);

#endif
