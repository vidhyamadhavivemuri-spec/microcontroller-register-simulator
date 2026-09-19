#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

void adc_start_conversion(void);

bool adc_is_conversion_complete(void);

int adc_read(void);

void adc_set_value(uint16_t value);

void adc_update(void);

#endif