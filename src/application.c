#include "application.h"
#include "events.h"
#include "adc.h"

static unsigned int timer_event_count = 0;
static int last_adc_value = -1;
static adc_state_t adc_state = ADC_NORMAL;
static unsigned int alert_event_count = 0;

void application_init(void)
{
    timer_event_count = 0;
    alert_event_count = 0;
    last_adc_value = -1;
    adc_state = ADC_NORMAL;

    events_clear_alert_event();
}

void application_process_events(void)
{
    /* Process Timer event */
    if (events_is_timer_event_pending())
    {
        timer_event_count++;
        events_clear_timer_event();
    }

    /* Process ADC event */
    if (events_is_adc_event_pending())
    {
        int value = adc_read();

        if (value >= 0)
        {
            last_adc_value = value;

            if (value >= 700)
            {
                adc_state = ADC_ALERT;
                events_set_alert_event();
            }
            else
            {
                adc_state = ADC_NORMAL;
                events_clear_alert_event();
            }
        }

        events_clear_adc_event();
    }

    /* Process Alert event */
    if (events_is_alert_event_pending())
    {
        alert_event_count++;
        events_clear_alert_event();
    }
}

unsigned int application_get_timer_event_count(void)
{
    return timer_event_count;
}

int application_get_last_adc_value(void)
{
    return last_adc_value;
}

adc_state_t application_get_adc_state(void)
{
    return adc_state;
}
unsigned int application_get_alert_event_count(void)
{
    return alert_event_count;
}