#ifndef WDT_H
#define WDT_H

#include <stdbool.h>

void wdt_enable(void);
void wdt_disable(void);
bool wdt_is_enabled(void);
void wdt_feed(void);
void wdt_update(void);

#endif
