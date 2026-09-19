#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include <stdbool.h>

void pwm_enable(void);

void pwm_disable(void);

bool pwm_is_enabled(void);

void pwm_set_duty(uint8_t duty);

uint8_t pwm_get_duty(void);

#endif