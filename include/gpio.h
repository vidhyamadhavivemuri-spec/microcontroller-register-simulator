#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void gpio_set_pin(uint8_t pin);
void gpio_clear_pin(uint8_t pin);
void gpio_toggle_pin(uint8_t pin);
int gpio_read_pin(uint8_t pin);

#endif