#ifndef APPLICATION_H
#define APPLICATION_H

typedef enum
{
    ADC_NORMAL,
    ADC_ALERT
} adc_state_t;
typedef enum
{
    ALERT_NOT_ACTIVE,
    ALERT_ACTIVE
} alert_status_t;
typedef enum
{
    ALERT_OUTPUT_OFF,
    ALERT_OUTPUT_ON
} alert_output_status_t;

void application_init(void);
void application_process_events(void);
alert_status_t application_get_alert_status(void);
alert_output_status_t application_get_alert_output_status(void);
unsigned int application_get_timer_event_count(void);
int application_get_last_adc_value(void);
adc_state_t application_get_adc_state(void);
unsigned int application_get_alert_event_count(void);

#endif