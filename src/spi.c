#include "spi.h"
#include "register.h"

static bool tx_in_progress = false;

void spi_init(void)
{
    SPI_CONTROL = 0;
    SPI_STATUS = 1;      // TX READY = 1
    SPI_DATA = 0;
    tx_in_progress = false;
}

void spi_enable(void)
{
    SPI_CONTROL |= (1U << 0);
}

void spi_disable(void)
{
    SPI_CONTROL &= ~(1U << 0);
}

bool spi_is_enabled(void)
{
    return (SPI_CONTROL & (1U << 0)) != 0;
}

bool spi_is_tx_ready(void)
{
    return (SPI_STATUS & (1U << 0)) != 0;
}

bool spi_is_rx_available(void)
{
    return (SPI_STATUS & (1U << 1)) != 0;
}

bool spi_write_data(uint8_t data)
{
    if ((SPI_CONTROL & (1U << 0)) == 0)
    {
        return false;
    }

    if ((SPI_STATUS & (1U << 0)) == 0)
    {
        return false;
    }

    SPI_DATA = data;
    SPI_STATUS &= ~(1U << 0);
    tx_in_progress = true;

    return true;
}

uint8_t spi_read_data(void)
{
    uint8_t data = SPI_DATA;

    SPI_STATUS &= ~(1U << 1);

    return data;
}

void spi_update(void)
{
    if (tx_in_progress)
    {
        SPI_STATUS |= (1U << 0);
        tx_in_progress = false;
    }
}
void spi_receive_data(uint8_t data)
{
    if ((SPI_CONTROL & (1U << 0)) == 0)
    {
        return;
    }

    SPI_DATA = data;
    SPI_STATUS |= (1U << 1);
}