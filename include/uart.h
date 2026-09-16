#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

bool uart_is_tx_ready(void);
void uart_clear_tx_ready(void);
bool uart_is_rx_data_available(void);

void uart_write_data(uint8_t data);
bool uart_send_byte(uint8_t data);
void uart_complete_transmission(void);
void uart_update(void);

#endif