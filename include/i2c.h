#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

void i2c_enable(void);
void i2c_disable(void);
bool i2c_is_enabled(void);

bool i2c_set_address(uint8_t address);
bool i2c_is_busy(void);

bool i2c_start(void);
void i2c_stop(void);

bool i2c_write_data(uint8_t data);

bool i2c_is_rx_available(void);
bool i2c_receive_data(uint8_t data);
uint8_t i2c_read_data(void);

#endif