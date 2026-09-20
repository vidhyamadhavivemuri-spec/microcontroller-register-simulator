#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include <stdbool.h>

void spi_init(void);

void spi_enable(void);
void spi_disable(void);
bool spi_is_enabled(void);

bool spi_is_tx_ready(void);
bool spi_is_rx_available(void);

bool spi_write_data(uint8_t data);
uint8_t spi_read_data(void);

void spi_update(void);
void spi_receive_data(uint8_t data);
#endif