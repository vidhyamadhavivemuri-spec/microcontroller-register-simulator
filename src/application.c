#include "application.h"
#include "events.h"

void application_process_events(void)
{
    if (events_is_timer_event_pending())
    {
        /* Handle Timer event. */
        events_clear_timer_event();
    }

    if (events_is_adc_event_pending())
    {
        /* Handle ADC event. */
        events_clear_adc_event();
    }
}