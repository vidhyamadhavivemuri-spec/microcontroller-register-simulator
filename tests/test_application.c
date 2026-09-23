#include <assert.h>
#include <stdio.h>

#include "application.h"
#include "events.h"

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

int main(void)
{
    test_timer_event_processing();
    test_adc_event_processing();
    test_both_events_processing();
    test_timer_event_count();

    printf("Application event processing tests passed!\n");

    return 0;
}