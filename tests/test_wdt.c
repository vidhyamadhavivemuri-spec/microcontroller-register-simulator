#include <stdio.h>

#include "register.h"
#include "wdt.h"

int main(void)
{
    printf("--- Watchdog Timer Test ---\n");

    printf("Initial WDT enabled = %d\n",
           wdt_is_enabled());

    wdt_enable();

    printf("WDT enabled after enable = %d\n",
           wdt_is_enabled());

    wdt_disable();

    printf("WDT enabled after disable = %d\n",
           wdt_is_enabled());
    printf("\n--- WDT Timeout Test ---\n");

    WDT_COUNT = 0;
    WDT_TIMEOUT = 3;
    WDT_STATUS = 0;

    wdt_enable();

    printf("Initial WDT_COUNT = %u\n",
           WDT_COUNT);

    wdt_update();

    printf("WDT_COUNT after update 1 = %u\n",
           WDT_COUNT);

    wdt_update();

    printf("WDT_COUNT after update 2 = %u\n",
           WDT_COUNT);

    wdt_update();

    printf("WDT_COUNT after update 3 = %u\n",
           WDT_COUNT);

    printf("WDT_STATUS after timeout = %u\n",
           WDT_STATUS);

    wdt_disable();
    printf("\n--- WDT Feed Test ---\n");

    WDT_COUNT = 2;
    WDT_TIMEOUT = 5;
    WDT_STATUS = 0;

    /*printf("WDT_COUNT before feed = %u\n", WDT_COUNT);*/
    wdt_enable();

    printf("WDT_COUNT before feed = %u\n", WDT_COUNT);
    wdt_feed();

    printf("WDT_COUNT after feed = %u\n", WDT_COUNT);

    wdt_update();

    printf("WDT_COUNT after update = %u\n", WDT_COUNT);

    printf("\n--- WDT Disabled Feed Test ---\n");

    wdt_disable();

    WDT_COUNT = 3;

    printf("WDT_COUNT before disabled feed = %u\n", WDT_COUNT);

    wdt_feed();

    printf("WDT_COUNT after disabled feed = %u\n", WDT_COUNT);
    printf("\n--- WDT Zero Timeout Test ---\n");

    wdt_enable();

    WDT_COUNT = 0;
    WDT_TIMEOUT = 0;
    WDT_STATUS = 0;

    wdt_update();

    printf("WDT_COUNT after update with timeout 0 = %u\n",
           WDT_COUNT);

    printf("WDT_STATUS after update with timeout 0 = %u\n",
           WDT_STATUS);
    printf("\n--- WDT Sticky Timeout Test ---\n");

    wdt_enable();

    WDT_COUNT = 0;
    WDT_TIMEOUT = 2;
    WDT_STATUS = 0;

    wdt_update();
    wdt_update();

    printf("WDT_STATUS after timeout = %u\n",
           WDT_STATUS);

    wdt_feed();

    printf("WDT_COUNT after feed = %u\n",
           WDT_COUNT);

    printf("WDT_STATUS after feed = %u\n",
           WDT_STATUS);
    return 0;
}