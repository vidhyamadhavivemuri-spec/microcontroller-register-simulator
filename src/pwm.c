#include "pwm.h"
#include "register.h"

void pwm_enable(void)
{
    PWM_CONTROL |= (1U << 0);
}

void pwm_disable(void)
{
    PWM_CONTROL &= ~(1U << 0);
}

bool pwm_is_enabled(void)
{
    return (PWM_CONTROL & (1U << 0)) != 0;
}

void pwm_set_duty(uint8_t duty)
{
    if (duty > 100)
    {
        duty = 100;
    }

    PWM_DUTY = duty;
}

uint8_t pwm_get_duty(void)
{
    return PWM_DUTY;
}