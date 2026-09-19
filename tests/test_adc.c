#include <stdio.h>

#include "register.h"
#include "adc.h"

int main(void)
{
    printf("--- ADC Test ---\n");

    /* Test 1: Read before conversion */
    printf("Initial ADC_STATUS = %u\n", ADC_STATUS);

    printf("Read before conversion = %d\n", adc_read());

    /* Set simulated ADC input */
    adc_set_value(750);

    printf("ADC_DATA = %u\n", ADC_DATA);

    /* Test 2: Start conversion */
    adc_start_conversion();

    printf("ADC_CONTROL after start = %u\n", ADC_CONTROL);

    /* Test 3: Complete conversion */
    adc_update();

    printf("ADC_CONTROL after update = %u\n", ADC_CONTROL);
    printf("ADC_STATUS after update = %u\n", ADC_STATUS);

    /* Test 4: Read converted value */
    printf("ADC read value = %d\n", adc_read());

    printf("ADC_STATUS after read = %u\n", ADC_STATUS);
    printf("\n--- ADC Range Test ---\n");

    adc_set_value(1500);

    printf("ADC_DATA after setting 1500 = %u\n", ADC_DATA);
    adc_set_value(1023);
    printf("ADC_DATA after setting 1023 = %u\n", ADC_DATA);

    adc_set_value(0);
    printf("ADC_DATA after setting 0 = %u\n", ADC_DATA);
    return 0;
}
