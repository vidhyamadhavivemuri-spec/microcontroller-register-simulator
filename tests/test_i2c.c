#include <stdio.h>

#include "register.h"
#include "i2c.h"

int main(void)
{
    printf("--- I2C Test ---\n");

    /* Enable / Disable Test */
    printf("Initial I2C enabled = %d\n",
           i2c_is_enabled());

    i2c_enable();

    printf("I2C enabled after enable = %d\n",
           i2c_is_enabled());

    i2c_disable();

    printf("I2C enabled after disable = %d\n",
           i2c_is_enabled());

    /* Address Test */
    printf("Set address 0x50 = %d\n",
           i2c_set_address(0x50));

    printf("I2C_ADDRESS = 0x%02X\n",
           I2C_ADDRESS);

    printf("Set address 0xFF = %d\n",
           i2c_set_address(0xFF));

    printf("I2C_ADDRESS after invalid address = 0x%02X\n",
           I2C_ADDRESS);

    /* START / STOP Test */
    printf("\n--- I2C START/STOP Test ---\n");

    printf("Initial BUSY = %d\n",
           i2c_is_busy());

    printf("Start while disabled = %d\n",
           i2c_start());

    printf("BUSY after rejected start = %d\n",
           i2c_is_busy());

    i2c_enable();

    printf("Start while enabled = %d\n",
           i2c_start());

    printf("BUSY after start = %d\n",
           i2c_is_busy());

    i2c_stop();

    printf("BUSY after stop = %d\n",
           i2c_is_busy());

    /* TX Test */
    printf("\n--- I2C TX Test ---\n");

    printf("Write while bus idle = %d\n",
           i2c_write_data('A'));

    printf("I2C_DATA after rejected write = 0x%02X\n",
           I2C_DATA);

    i2c_start();

    printf("Write while bus busy = %d\n",
           i2c_write_data('A'));

    printf("I2C_DATA after write = %c\n",
           I2C_DATA);

    i2c_stop();

    printf("Write after stop = %d\n",
           i2c_write_data('B'));

    printf("I2C_DATA after rejected write = %c\n",
           I2C_DATA);

    /* RX Test */
    printf("\n--- I2C RX Test ---\n");

    printf("RX available initially = %d\n",
           i2c_is_rx_available());

    printf("Receive while bus idle = %d\n",
           i2c_receive_data('X'));

    printf("RX available after rejected receive = %d\n",
           i2c_is_rx_available());

    i2c_start();

    printf("Receive while bus busy = %d\n",
           i2c_receive_data('X'));

    printf("I2C_DATA after receive = %c\n",
           I2C_DATA);

    printf("RX available after receive = %d\n",
           i2c_is_rx_available());

    printf("Read received data = %c\n",
           i2c_read_data());

    printf("RX available after read = %d\n",
           i2c_is_rx_available());

    i2c_stop();

    /* RX Read Without Data Test */
    printf("\n--- I2C RX Empty Read Test ---\n");

    printf("RX available before empty read = %d\n",
           i2c_is_rx_available());

    printf("Data returned from empty read = 0x%02X\n",
           i2c_read_data());

    printf("RX available after empty read = %d\n",
           i2c_is_rx_available());

    /* RX Disabled Test */
    printf("\n--- I2C RX Disabled Test ---\n");

    i2c_disable();

    printf("Receive while I2C disabled = %d\n",
           i2c_receive_data('D'));

    printf("RX available after disabled receive = %d\n",
           i2c_is_rx_available());
    printf("\n--- I2C RX Overwrite Test ---\n");

    i2c_enable();
    i2c_start();

    printf("Receive first byte = %d\n",
           i2c_receive_data('A'));

    printf("I2C_DATA after first byte = %c\n",
           I2C_DATA);

    printf("Receive second byte = %d\n",
           i2c_receive_data('B'));

    printf("I2C_DATA after second byte = %c\n",
           I2C_DATA);

    printf("RX available = %d\n",
           i2c_is_rx_available());

    printf("Read received data = %c\n",
           i2c_read_data());

    printf("RX available after read = %d\n",
           i2c_is_rx_available());

    i2c_stop();
    return 0;
}
