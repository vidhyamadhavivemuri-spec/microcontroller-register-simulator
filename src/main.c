#include <stdio.h>
#include "register.h"
#include "gpio.h"

int main(void)
{
    printf("Initial GPIOA_ODR = %u\n", GPIOA_ODR);

    /* Set bit 5 */
    gpio_set_pin(5);
    printf("After setting bit 5 = %u\n", GPIOA_ODR);

    /* Set bit 2 */
    gpio_set_pin(2);
    printf("After setting bit 2 = %u\n", GPIOA_ODR);

    /* Clear bit 2 */
    gpio_clear_pin(2);
    printf("After clearing bit 2 = %u\n", GPIOA_ODR);

    /* Toggle bit 5 */
    gpio_toggle_pin(5);
    printf("After toggling bit 5 = %u\n", GPIOA_ODR);

    /* Read bit 5 */
    printf("Pin 5 state = %d\n", gpio_read_pin(5));

    /* Test highest valid pin */
    gpio_set_pin(31);
    printf("After setting bit 31 = %u\n", GPIOA_ODR);

    /* Test invalid pin */
    gpio_set_pin(32);
    printf("After trying to set bit 32 = %u\n", GPIOA_ODR);

    /* Read invalid pin */
    printf("Reading invalid pin 32 = %d\n", gpio_read_pin(32));

    return 0;
}