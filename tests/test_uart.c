#include <stdio.h>
#include <stdbool.h>

#include "register.h"
#include "uart.h"

int main(void)
{
    /* ================= UART TX TESTS ================= */

    printf("\n--- UART TX Tests ---\n");

    UART_STATUS = 0;

    printf("Initial TX Ready = %d\n",
           uart_is_tx_ready());

    bool success = uart_send_byte('A');

    printf("Sending 'A' when TX not ready = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = %u\n",
           UART_DATA);

    UART_STATUS |= (1U << 0);

    printf("\nTX Ready after setting flag = %d\n",
           uart_is_tx_ready());

    success = uart_send_byte('A');

    printf("Sending 'A' when TX ready = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = '%c' (0x%02X)\n",
           UART_DATA, UART_DATA);

    printf("TX Ready after sending = %d\n",
           uart_is_tx_ready());

    success = uart_send_byte('B');

    printf("Sending 'B' immediately = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = '%c'\n",
           UART_DATA);


    /* ================= AUTOMATIC TX COMPLETION ================= */

    printf("\n--- Automatic TX Completion Tests ---\n");

    printf("Waiting for transmission to complete...\n");

    while (!uart_is_tx_ready())
    {
        uart_update();
    }

    printf("TX Ready after automatic completion = %d\n",
           uart_is_tx_ready());

    bool success_B_retry = uart_send_byte('B');

    printf("Retry sending 'B' status = %s\n",
           success_B_retry ? "SUCCESS" : "FAILED");

    printf("New UART_DATA contains = '%c' (0x%02X)\n",
           UART_DATA, UART_DATA);

    printf("TX Ready after sending B = %d\n",
           uart_is_tx_ready());


    /* ================= UART RX TEST ================= */

    printf("\n--- UART RX Status Tests ---\n");

    UART_STATUS = 0;

    printf("RX Available = %d\n",
           uart_is_rx_data_available());

    UART_STATUS |= (1U << 1);

    printf("RX Available after setting flag = %d\n",
           uart_is_rx_data_available());


    return 0;
}