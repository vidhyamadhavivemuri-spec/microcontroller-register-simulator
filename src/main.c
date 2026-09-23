#include <stdio.h>

#include "register.h"
#include "timer.h"
#include "adc.h"
#include "interrupt.h"
#include "events.h"
#include "application.h"


/* Timer interrupt handler */
void timer_handler(void)
{
    events_set_timer_event();
}

/* ADC interrupt handler */
void adc_handler(void)
{
    events_set_adc_event();
}

int main(void)
{
    printf("--- Microcontroller Register Simulator ---\n\n");

    /* ================= INITIALIZATION ================= */

    printf("--- System Initialization ---\n");

    interrupt_init();
    application_init();

    interrupt_register_handler(0, timer_handler);
    interrupt_register_handler(1, adc_handler);

    interrupt_int0_enable();
    interrupt_int1_enable();

    printf("INT_ENABLE = %u\n", INT_ENABLE);

    /* ================= TIMER EVENT ================= */

    printf("\n--- Timer Event Simulation ---\n");

    TIMER_COUNT = 255;
    TIMER_CONTROL = 0;
    TIMER_STATUS = 0;

    timer_start();

    timer_update();

    printf("Timer Count = %u\n", TIMER_COUNT);
    printf("Timer Overflow = %s\n",
           (TIMER_STATUS & (1U << 0)) ? "YES" : "NO");

    printf("INT_PENDING = %u\n", INT_PENDING);

    /* Service Timer interrupt. */
    interrupt_service_next();

    printf("INT_PENDING after interrupt service = %u\n",
           INT_PENDING);

    printf("Timer Event Pending = %s\n",
           events_is_timer_event_pending() ? "YES" : "NO");

    /* Application processes Timer event. */
    application_process_events();
    printf("Timer Events Processed = %u\n",
       application_get_timer_event_count());

    printf("Timer Event Pending after application processing = %s\n",
           events_is_timer_event_pending() ? "YES" : "NO");

    /* ================= ADC EVENT ================= */

    printf("\n--- ADC Event Simulation ---\n");

    ADC_CONTROL = 0;
    ADC_STATUS = 0;
    ADC_DATA = 0;

    adc_set_value(512);
    adc_start_conversion();

    adc_update();

    printf("ADC Data = %u\n", ADC_DATA);
    printf("ADC Conversion Complete = %s\n",
           adc_is_conversion_complete() ? "YES" : "NO");

    printf("INT_PENDING = %u\n", INT_PENDING);

    /* Service ADC interrupt. */
    interrupt_service_next();

    printf("INT_PENDING after interrupt service = %u\n",
           INT_PENDING);

    printf("ADC Event Pending = %s\n",
           events_is_adc_event_pending() ? "YES" : "NO");

    /* Application processes ADC event. */
    application_process_events();

    printf("ADC Event Pending after application processing = %s\n",
           events_is_adc_event_pending() ? "YES" : "NO");

    /* ================= COMPLETE ================= */

    printf("\n--- Application Simulation Complete ---\n");

    return 0;
}