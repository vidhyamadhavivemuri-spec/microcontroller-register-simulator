#include "i2c.h"
#include "register.h"

void i2c_enable(void)
{
    I2C_CONTROL |= (1U << 0);
}

void i2c_disable(void)
{
    I2C_CONTROL &= ~(1U << 0);
}

bool i2c_is_enabled(void)
{
    return (I2C_CONTROL & (1U << 0)) != 0;
}

bool i2c_set_address(uint8_t address)
{
    if (address > 0x7F)
    {
        return false;
    }

    I2C_ADDRESS = address;

    return true;
}

bool i2c_is_busy(void)
{
    return (I2C_STATUS & (1U << 0)) != 0;
}

bool i2c_start(void)
{
    if (!i2c_is_enabled())
    {
        return false;
    }

    I2C_STATUS |= (1U << 0);

    return true;
}

void i2c_stop(void)
{
    I2C_STATUS &= ~(1U << 0);
}

bool i2c_write_data(uint8_t data)
{
    if (!i2c_is_enabled() || !i2c_is_busy())
    {
        return false;
    }

    I2C_DATA = data;

    return true;
}

bool i2c_is_rx_available(void)
{
    return (I2C_STATUS & (1U << 1)) != 0;
}

bool i2c_receive_data(uint8_t data)
{
    if (!i2c_is_enabled() || !i2c_is_busy())
    {
        return false;
    }

    I2C_DATA = data;
    I2C_STATUS |= (1U << 1);

    return true;
}

uint8_t i2c_read_data(void)
{
    uint8_t data = I2C_DATA;

    if (i2c_is_rx_available())
    {
        I2C_STATUS &= ~(1U << 1);
    }

    return data;
}