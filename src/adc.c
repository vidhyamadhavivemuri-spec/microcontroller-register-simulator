#include "adc.h"
#include "register.h"
#include "interrupt.h"

bool adc_is_conversion_complete(void)
{
    return (ADC_STATUS & (1U << 0)) != 0;
}

void adc_start_conversion(void)
{
    ADC_CONTROL |= (1U << 0);
}

void adc_set_value(uint16_t value)
{
    if (value > 1023)
    {
        ADC_DATA = 1023;
    }
    else
    {
        ADC_DATA = value;
    }
}

int adc_read(void)
{
    if ((ADC_STATUS & (1U << 0)) == 0)
    {
        return -1;
    }

    int value = ADC_DATA;

    ADC_STATUS &= ~(1U << 0);

    return value;
}

void adc_update(void)
{
    if ((ADC_CONTROL & (1U << 0)) == 0)
    {
        return;
    }

    ADC_STATUS |= (1U << 0);

    interrupt_int1_trigger();

    ADC_CONTROL &= ~(1U << 0);
}