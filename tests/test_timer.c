#include <stdio.h>

#include "register.h"
#include "timer.h"
#include "interrupt.h"

int main(void)
{
    /* ================= TIMER TEST ================= */

    printf("--- Timer Test ---\n");

    TIMER_COUNT = 0;
    TIMER_CONTROL = 0;
    TIMER_STATUS = 0;

    printf("Initial Timer Enable = %d\n",
           (TIMER_CONTROL & (1U << 0)) != 0);

    printf("Initial Timer Count = %u\n",
           TIMER_COUNT);

    timer_start();

    printf("Timer Enable after start = %d\n",
           (TIMER_CONTROL & (1U << 0)) != 0);

    timer_update();

    printf("Timer Count after update = %u\n",
           TIMER_COUNT);

    timer_stop();

    printf("Timer Enable after stop = %d\n",
           (TIMER_CONTROL & (1U << 0)) != 0);

    timer_update();

    printf("Timer Count after update while stopped = %u\n",
           TIMER_COUNT);


    /* ================= TIMER OVERFLOW TEST ================= */

    printf("\n--- Timer Overflow Test ---\n");

    TIMER_COUNT = 255;
    TIMER_CONTROL = 0;
    TIMER_STATUS = 0;

    timer_start();

    printf("Timer Count before overflow = %u\n",
           TIMER_COUNT);

    timer_update();

    printf("Timer Count after overflow = %u\n",
           TIMER_COUNT);

    printf("Overflow Flag = %d\n",
           (TIMER_STATUS & (1U << 0)) != 0);


    /* ================= STICKY OVERFLOW TEST ================= */

    printf("\n--- Sticky Overflow Test ---\n");

    TIMER_COUNT = 255;
    TIMER_STATUS = 0;
    TIMER_CONTROL = 0;

    timer_start();

    timer_update();

    printf("Overflow Flag after overflow = %d\n",
           (TIMER_STATUS & (1U << 0)) != 0);

    timer_update();

    printf("Timer Count after another update = %u\n",
           TIMER_COUNT);

    printf("Overflow Flag after another update = %d\n",
           (TIMER_STATUS & (1U << 0)) != 0);

    timer_clear_overflow();

    printf("Overflow Flag after software clear = %d\n",
           (TIMER_STATUS & (1U << 0)) != 0);


    return 0;
}