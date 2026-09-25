#ifndef APPLICATION_H
#define APPLICATION_H

void application_init(void);
void application_process_events(void);

unsigned int application_get_timer_event_count(void);
int application_get_last_adc_value(void);

#endif
