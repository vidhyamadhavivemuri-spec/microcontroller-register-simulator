#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

/* GPIO register */
extern uint32_t GPIOA_ODR;

/* UART registers */
extern uint32_t UART_DATA;
extern uint32_t UART_STATUS;
extern uint32_t UART_CONTROL;

/* Timer registers */
extern uint32_t TIMER_COUNT;
extern uint32_t TIMER_CONTROL;
extern uint32_t TIMER_STATUS;
extern uint32_t INT_ENABLE;
extern uint32_t INT_PENDING;

/* ADC registers */

extern uint32_t ADC_DATA;
extern uint32_t ADC_CONTROL;
extern uint32_t ADC_STATUS;

/* PWM registers */

extern uint32_t PWM_DUTY;

extern uint32_t PWM_CONTROL;

extern uint32_t PWM_STATUS;

extern uint32_t SPI_DATA;
extern uint32_t SPI_CONTROL;
extern uint32_t SPI_STATUS;

/* I2C registers */
extern uint32_t I2C_DATA;
extern uint32_t I2C_ADDRESS;
extern uint32_t I2C_CONTROL;
extern uint32_t I2C_STATUS;
#endif
