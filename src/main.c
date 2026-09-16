#include <stdio.h>
#include <stdbool.h>

#include "register.h"
#include "gpio.h"
#include "uart.h"

int main(void)
{
    printf("--- Microcontroller Register Simulator ---\n\n");

    /* ================= GPIO TESTS ================= */

    printf("--- GPIO Register Test ---\n");

    printf("Initial GPIOA_ODR = %u\n", GPIOA_ODR);

    gpio_set_pin(5);
    printf("After setting bit 5 = %u\n", GPIOA_ODR);

    gpio_set_pin(2);
    printf("After setting bit 2 = %u\n", GPIOA_ODR);

    gpio_clear_pin(2);
    printf("After clearing bit 2 = %u\n", GPIOA_ODR);

    gpio_toggle_pin(5);
    printf("After toggling bit 5 = %u\n", GPIOA_ODR);

    printf("Pin 5 state = %d\n", gpio_read_pin(5));

    gpio_set_pin(31);
    printf("After setting bit 31 = %u\n", GPIOA_ODR);

    gpio_set_pin(32);
    printf("After trying to set bit 32 = %u\n", GPIOA_ODR);

    printf("Reading invalid pin 32 = %d\n", gpio_read_pin(32));


    /* ================= UART TX TESTS ================= */

    printf("\n--- UART TX Test ---\n");

    /* Initially transmitter is not ready */
    UART_STATUS = 0;

    printf("Initial TX Ready = %d\n",
           uart_is_tx_ready());

    /* Try sending when transmitter is not ready */
    bool success = uart_send_byte('A');

    printf("Sending 'A' when TX not ready = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = %u\n", UART_DATA);


    /* Set TX Ready */
    UART_STATUS |= (1U << 0);

    printf("\nTX Ready after setting flag = %d\n",
           uart_is_tx_ready());


    /* Send A */
    success = uart_send_byte('A');

    printf("Sending 'A' when TX ready = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = '%c' (0x%02X)\n",
           UART_DATA, UART_DATA);

    printf("TX Ready after sending = %d\n",
           uart_is_tx_ready());


    /* Try sending B while transmitter is busy */
    success = uart_send_byte('B');

    printf("Sending 'B' immediately = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = '%c'\n", UART_DATA);


    /* ================= AUTOMATIC TX COMPLETION ================= */

    printf("\n--- Automatic TX Completion Test ---\n");

    printf("Waiting for transmission to complete...\n");

    while (!uart_is_tx_ready())
    {
        uart_update();
    }

    printf("TX Ready after automatic completion = %d\n",
           uart_is_tx_ready());


    /* Try sending B again */
    bool success_B_retry = uart_send_byte('B');

    printf("Retry sending 'B' status = %s\n",
           success_B_retry ? "SUCCESS" : "FAILED");

    printf("New UART_DATA contains = '%c' (0x%02X)\n",
           UART_DATA, UART_DATA);

    printf("TX Ready after sending B = %d\n",
           uart_is_tx_ready());


    /* ================= UART RX TEST ================= */

    printf("\n--- UART RX Status Test ---\n");

    UART_STATUS = 0;

    printf("RX Available = %d\n",
           uart_is_rx_data_available());

    UART_STATUS |= (1U << 1);

    printf("RX Available after setting flag = %d\n",
           uart_is_rx_data_available());


    return 0;
}