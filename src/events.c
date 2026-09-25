#include "events.h"

static bool timer_event_pending = false;
static bool adc_event_pending = false;
static bool alert_event_pending = false;

/* Timer event */

void events_set_timer_event(void)
{
    timer_event_pending = true;
}

bool events_is_timer_event_pending(void)
{
    return timer_event_pending;
}

void events_clear_timer_event(void)
{
    timer_event_pending = false;
}

/* ADC event */

void events_set_adc_event(void)
{
    adc_event_pending = true;
}

bool events_is_adc_event_pending(void)
{
    return adc_event_pending;
}

void events_clear_adc_event(void)
{
    adc_event_pending = false;
}

/* Alert event */

void events_set_alert_event(void)
{
    alert_event_pending = true;
}

bool events_is_alert_event_pending(void)
{
    return alert_event_pending;
}

void events_clear_alert_event(void)
{
    alert_event_pending = false;
}