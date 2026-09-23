#ifndef EVENTS_H
#define EVENTS_H

#include <stdbool.h>

/* Timer event */
void events_set_timer_event(void);
bool events_is_timer_event_pending(void);
void events_clear_timer_event(void);

/* ADC event */
void events_set_adc_event(void);
bool events_is_adc_event_pending(void);
void events_clear_adc_event(void);

#endif
