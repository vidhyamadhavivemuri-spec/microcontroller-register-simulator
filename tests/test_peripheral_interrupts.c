#include <assert.h>
#include <stdio.h>

#include "timer.h"
#include "adc.h"
#include "interrupt.h"
#include "register.h"

static int timer_handler_called = 0;
static int adc_handler_called = 0;
void test_timer_handler(void)
{
    timer_handler_called++;
}
void test_timer_interrupt_handler(void)
{
    interrupt_init();

    timer_handler_called = 0;

    interrupt_register_handler(0, test_timer_handler);
    interrupt_int0_enable();

    TIMER_COUNT = 0;
    TIMER_CONTROL = 0;
    TIMER_STATUS = 0;

    timer_start();

    TIMER_COUNT = 255;
    timer_update();

    assert(TIMER_STATUS == 1);
    assert(INT_PENDING == 1);

    assert(interrupt_service_next() == true);

    assert(INT_PENDING == 0);
    assert(timer_handler_called == 1);
}
void test_adc_handler(void)
{
    adc_handler_called++;
}
void test_adc_interrupt_handler(void)
{
    interrupt_init();

    adc_handler_called = 0;

    interrupt_register_handler(1, test_adc_handler);
    interrupt_int1_enable();

    ADC_CONTROL = 0;
    ADC_STATUS = 0;
    ADC_DATA = 0;

    adc_start_conversion();
    adc_update();

    assert(ADC_STATUS == 1);
    assert(INT_PENDING == 2);

    assert(interrupt_service_next() == true);

    assert(INT_PENDING == 0);
    assert(adc_handler_called == 1);
}

int main(void)
{
    test_timer_interrupt_handler();
    test_adc_interrupt_handler();

    printf("Peripheral interrupt integration tests passed!\n");

    return 0;
}