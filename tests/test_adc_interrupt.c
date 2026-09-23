#include <assert.h>
#include <stdio.h>

#include "adc.h"
#include "interrupt.h"
#include "register.h"

void test_adc_triggers_int1(void)
{
    /* Reset ADC registers to a known state. */
    ADC_CONTROL = 0;
    ADC_STATUS  = 0;
    ADC_DATA    = 0;

    /* Initialize interrupt controller and enable INT1. */
    interrupt_init();
    interrupt_int1_enable();

    /* INT_PENDING should initially be clear. */
    assert(INT_PENDING == 0);

    /* Start and complete one ADC conversion. */
    adc_start_conversion();
    adc_update();

    /* ADC conversion must set COMPLETE. */
    assert(ADC_STATUS == 1);

    /* ADC completion must trigger INT1. */
    assert(INT_PENDING == 2);

    /* Service INT1. */
    interrupt_service_int1();

    /* INT1 should no longer be pending. */
    assert(INT_PENDING == 0);
}

void test_adc_interrupt_when_disabled(void)
{
    ADC_CONTROL = 0;
    ADC_STATUS = 0;
    ADC_DATA = 0;

    interrupt_init();

    assert(INT_PENDING == 0);

    adc_start_conversion();
    adc_update();

    assert(ADC_STATUS == 1);
    assert(INT_PENDING == 2);

    assert(interrupt_service_int1() == false);
    assert(INT_PENDING == 2);
}

int main(void)
{
    test_adc_triggers_int1();
    test_adc_interrupt_when_disabled();

    printf("ADC -> INT1 integration tests passed!\n");

    return 0;
}