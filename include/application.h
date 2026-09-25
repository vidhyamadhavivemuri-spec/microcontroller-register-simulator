#ifndef APPLICATION_H
#define APPLICATION_H

typedef enum
{
    ADC_NORMAL,
    ADC_ALERT
} adc_state_t;

void application_init(void);
void application_process_events(void);

unsigned int application_get_timer_event_count(void);
int application_get_last_adc_value(void);
adc_state_t application_get_adc_state(void);

#endif