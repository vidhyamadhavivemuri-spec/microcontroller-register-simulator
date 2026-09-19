#include <stdio.h>

#include "register.h"
#include "pwm.h"

int main(void)
{
    printf("--- PWM Test ---\n");

    printf("Initial PWM Enabled = %d\n", pwm_is_enabled());
    pwm_enable();
    printf("PWM Enabled after enable = %d\n", pwm_is_enabled());
    pwm_disable();
    printf("PWM Enabled after disable = %d\n", pwm_is_enabled());
    pwm_set_duty(75);
    printf("PWM Duty = %u\n", pwm_get_duty());
    pwm_set_duty(150);
    printf("PWM Duty after setting 150 = %u\n", pwm_get_duty());
    return 0;
}