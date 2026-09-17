#include <stdio.h>

#include "register.h"
#include "gpio.h"

int main(void)
{
    printf("--- GPIO Register Test ---\n");

    printf("Initial GPIOA_ODR = %u\n", GPIOA_ODR);

    gpio_set_pin(5);
    printf("After setting bit 5 = %u\n", GPIOA_ODR);

    gpio_set_pin(2);
    printf("After setting bit 2 = %u\n", GPIOA_ODR);

    gpio_clear_pin(2);
    printf("After clearing bit 2 = %u\n", GPIOA_ODR);

    gpio_toggle_pin(5);
    printf("After toggling bit 5 = %u\n", GPIOA_ODR);

    printf("Pin 5 state = %d\n", gpio_read_pin(5));

    gpio_set_pin(31);
    printf("After setting bit 31 = %u\n", GPIOA_ODR);

    gpio_set_pin(32);
    printf("After trying to set bit 32 = %u\n", GPIOA_ODR);

    printf("Reading invalid pin 32 = %d\n",
           gpio_read_pin(32));

    return 0;
}