#include "gpio.h"
#include "register.h"

static int gpio_valid_pin(uint8_t pin)
{
    return pin < 32;
}

void gpio_set_pin(uint8_t pin)
{
    if (!gpio_valid_pin(pin))
        return;

    GPIOA_ODR |= (1U << pin);
}

void gpio_clear_pin(uint8_t pin)
{
    if (!gpio_valid_pin(pin))
        return;

    GPIOA_ODR &= ~(1U << pin);
}

void gpio_toggle_pin(uint8_t pin)
{
    if (!gpio_valid_pin(pin))
        return;

    GPIOA_ODR ^= (1U << pin);
}

int gpio_read_pin(uint8_t pin)
{
    if (!gpio_valid_pin(pin))
        return -1;

    return (GPIOA_ODR & (1U << pin)) != 0;
}