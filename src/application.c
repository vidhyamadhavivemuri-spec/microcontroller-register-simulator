#include "application.h"
#include "events.h"

static unsigned int timer_event_count = 0;

void application_init(void)
{
    timer_event_count = 0;
}

void application_process_events(void)
{
    if (events_is_timer_event_pending())
    {
        timer_event_count++;
        events_clear_timer_event();
    }

    if (events_is_adc_event_pending())
    {
        /* Handle ADC event. */
        events_clear_adc_event();
    }
}

unsigned int application_get_timer_event_count(void)
{
    return timer_event_count;
}