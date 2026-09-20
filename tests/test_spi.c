#include <stdio.h>

#include "register.h"
#include "spi.h"

int main(void)
{
    printf("--- SPI Test ---\n");

    /* Initialize SPI */
    spi_init();

    /* 1. Initial state */
    printf("SPI enabled = %d\n", spi_is_enabled());
    printf("TX ready = %d\n", spi_is_tx_ready());
    printf("RX available = %d\n", spi_is_rx_available());

    /* 2. Enable SPI */
    spi_enable();
    printf("SPI enabled after enable = %d\n",
           spi_is_enabled());

    /* 3. Transmit a byte */
    printf("Write A = %d\n",
           spi_write_data('A'));

    printf("SPI_DATA = %c\n",
           SPI_DATA);

    printf("TX ready after write = %d\n",
           spi_is_tx_ready());

    /* 4. Try transmitting while busy */
    printf("Write B while busy = %d\n",
           spi_write_data('B'));

    printf("SPI_DATA after rejected write = %c\n",
           SPI_DATA);

    /* 5. Complete transmission */
    spi_update();

    printf("TX ready after update = %d\n",
           spi_is_tx_ready());

    /* 6. Transmit another byte */
    printf("Write B after update = %d\n",
           spi_write_data('B'));

    printf("SPI_DATA after B = %c\n",
           SPI_DATA);

    /* 7. Complete B transmission */
    spi_update();

    /* 8. Disable SPI */
    spi_disable();

    printf("SPI enabled after disable = %d\n",
           spi_is_enabled());

    printf("TX ready while SPI disabled = %d\n",
           spi_is_tx_ready());

    /* 9. Try transmitting while SPI is disabled */
    printf("Write C while SPI disabled = %d\n",
           spi_write_data('C'));

    printf("SPI_DATA after disabled write = %c\n",
           SPI_DATA);
    printf("\n--- SPI RX Test ---\n");
    spi_enable();
    printf("RX available before receive = %d\n",
           spi_is_rx_available());

    spi_receive_data('X');

    printf("RX available after receive = %d\n",
           spi_is_rx_available());

    printf("Received data = %c\n",
           spi_read_data());

    printf("RX available after read = %d\n",
           spi_is_rx_available());

    printf("\n--- SPI RX Overwrite Test ---\n");

    spi_receive_data('Y');

    printf("RX available after receiving Y = %d\n",
           spi_is_rx_available());

    spi_receive_data('Z');

    printf("SPI_DATA after receiving Z = %c\n",
           SPI_DATA);

    printf("RX available after receiving Z = %d\n",
           spi_is_rx_available());

    printf("Read received data = %c\n",
           spi_read_data());

    printf("RX available after read = %d\n",
           spi_is_rx_available());
    printf("\n--- SPI RX Disabled Test ---\n");

    spi_disable();

    spi_receive_data('D');

    printf("RX available after disabled receive = %d\n",
           spi_is_rx_available());

    printf("SPI_DATA after disabled receive = %c\n",
           SPI_DATA);
    return 0;
}