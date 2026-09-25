#include <assert.h>
#include <stdio.h>

#include "application.h"
#include "events.h"
#include "adc.h"
#include "interrupt.h"
#include "register.h"

void test_timer_event_processing(void)
{
    application_init();
    events_clear_timer_event();

    events_set_timer_event();

    assert(events_is_timer_event_pending() == true);

    application_process_events();

    assert(events_is_timer_event_pending() == false);
}

void test_adc_event_processing(void)
{
    application_init();
    events_clear_adc_event();

    events_set_adc_event();

    assert(events_is_adc_event_pending() == true);

    application_process_events();

    assert(events_is_adc_event_pending() == false);
}

void test_both_events_processing(void)
{
    application_init();
    events_clear_timer_event();
    events_clear_adc_event();

    events_set_timer_event();
    events_set_adc_event();

    assert(events_is_timer_event_pending() == true);
    assert(events_is_adc_event_pending() == true);

    application_process_events();

    assert(events_is_timer_event_pending() == false);
    assert(events_is_adc_event_pending() == false);
}

void test_timer_event_count(void)
{
    application_init();
    events_clear_timer_event();

    assert(application_get_timer_event_count() == 0);

    events_set_timer_event();

    application_process_events();

    assert(application_get_timer_event_count() == 1);

    /* No new event, so the count must remain 1. */
    application_process_events();

    assert(application_get_timer_event_count() == 1);
}

void test_adc_handler(void)
{
    events_set_adc_event();
}

void test_adc_value_processing(void)
{
    application_init();
    interrupt_init();

    interrupt_register_handler(1, test_adc_handler);
    interrupt_int1_enable();

    ADC_CONTROL = 0;
    ADC_STATUS = 0;
    ADC_DATA = 0;

    adc_set_value(512);
    adc_start_conversion();
    adc_update();

    interrupt_service_next();

    assert(events_is_adc_event_pending() == true);

    application_process_events();

    assert(application_get_last_adc_value() == 512);
    assert(events_is_adc_event_pending() == false);
}

int main(void)
{
    test_timer_event_processing();
    test_adc_event_processing();
    test_both_events_processing();
    test_timer_event_count();
    test_adc_value_processing();

    printf("Application event processing tests passed!\n");

    return 0;
}