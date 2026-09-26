#include "application.h"
#include "events.h"
#include "adc.h"
#include "alert_output.h"

static unsigned int timer_event_count = 0;
static int last_adc_value = -1;
static adc_state_t adc_state = ADC_NORMAL;
static unsigned int alert_event_count = 0;
static alert_status_t alert_status = ALERT_NOT_ACTIVE;
static alert_output_status_t alert_output_status = ALERT_OUTPUT_OFF;

void application_init(void)
{
    system_init();

    timer_event_count = 0;
    alert_event_count = 0;
    last_adc_value = -1;
    adc_state = ADC_NORMAL;
    alert_status = ALERT_NOT_ACTIVE;
    alert_output_status = ALERT_OUTPUT_OFF;
    alert_output_init();

    events_clear_alert_event();
}

void application_process_events(void)
{
    system_update();

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
                alert_status = ALERT_NOT_ACTIVE;
                alert_output_status = ALERT_OUTPUT_OFF;
                alert_output_off();
                system_clear_alert();
                events_clear_alert_event();
            }
        }

        events_clear_adc_event();
    }

    /* Process Alert event */
    if (events_is_alert_event_pending())
    {
        system_set_alert();

        alert_event_count++;
        alert_status = ALERT_ACTIVE;
        alert_output_status = ALERT_OUTPUT_ON;
        alert_output_on();
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

alert_status_t application_get_alert_status(void)
{
    return alert_status;
}
alert_output_status_t application_get_alert_output_status(void)
{
    return alert_output_status;
}
