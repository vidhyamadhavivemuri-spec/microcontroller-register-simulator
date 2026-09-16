#include "uart.h"
#include "register.h"
#include <time.h>

#define UART_TX_TIME 100

static clock_t tx_start_time;
static bool tx_in_progress = false;

bool uart_is_tx_ready(void)
{
    return (UART_STATUS & (1U << 0)) != 0;
}

void uart_clear_tx_ready(void)
{
    UART_STATUS &= ~(1U << 0);
}
bool uart_is_rx_data_available(void)
{
    return (UART_STATUS & (1U << 1)) != 0;
}
void uart_write_data(uint8_t data)
{
    UART_DATA = data;
}
bool uart_send_byte(uint8_t data)
{
    if ((UART_STATUS & (1U << 0)) == 0) {
        return false;
    }

    UART_DATA = data;
    UART_STATUS &= ~(1U << 0);
    tx_start_time = clock();
    tx_in_progress = true;
    return true;
}
void uart_complete_transmission(void)
{
    UART_STATUS |= (1U << 0);
}
void uart_update(void)
{
    if (tx_in_progress)
    {
        clock_t elapsed = clock() - tx_start_time;

        if ((elapsed * 1000 / CLOCKS_PER_SEC) >= UART_TX_TIME)
        {
            UART_STATUS |= (1U << 0);
            tx_in_progress = false;
        }
    }
}