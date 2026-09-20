#include "wdt.h"
#include "register.h"

void wdt_enable(void)
{
    WDT_CONTROL |= (1U << 0);
}

void wdt_disable(void)
{
    WDT_CONTROL &= ~(1U << 0);
}

bool wdt_is_enabled(void)
{
    return (WDT_CONTROL & (1U << 0)) != 0;
}

void wdt_feed(void)
{
    if (!wdt_is_enabled())
    {
        return;
    }

    WDT_COUNT = 0;
}

void wdt_update(void)
{
    if (!wdt_is_enabled())
    {
        return;
    }

    if (WDT_TIMEOUT == 0)
    {
        return;
    }

    WDT_COUNT++;

    if (WDT_COUNT >= WDT_TIMEOUT)
    {
        WDT_STATUS |= (1U << 0);
        WDT_COUNT = 0;
    }
}
