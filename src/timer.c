#include "timer.h"
#include "register.h"
#include "interrupt.h"
void timer_start(void)
{
    TIMER_CONTROL |= (1U << 0);
}

void timer_stop(void)
{
    TIMER_CONTROL &= ~(1U << 0);
}

void timer_update(void)
{
    /* Do nothing if timer is stopped */
    if (!(TIMER_CONTROL & (1U << 0)))
    {
        return;
    }

    /* Simulate an 8-bit counter */
    TIMER_COUNT = (TIMER_COUNT + 1) & 0xFF;

    /* Detect overflow */
    if (TIMER_COUNT == 0)
    {
        TIMER_STATUS |= (1U << 0);
        interrupt_int0_trigger();
    }
}
void timer_clear_overflow(void)
{
    TIMER_STATUS &= ~(1U << 0);
}