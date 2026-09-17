#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>
#include <stdbool.h>

#define INT0_BIT_MASK (1U << 0)
#define INT1_BIT_MASK (1U << 1)

/* Interrupt controller initialization */
void interrupt_init(void);

/* INT0 control */
void interrupt_int0_enable(void);
void interrupt_int0_disable(void);
void interrupt_int0_trigger(void);
void interrupt_int0_clear(void);
bool interrupt_int0_is_pending_and_enabled(void);
bool interrupt_service_int0(void);

/* INT1 control */
void interrupt_int1_enable(void);
void interrupt_int1_disable(void);
void interrupt_int1_trigger(void);
void interrupt_int1_clear(void);
bool interrupt_service_int1(void);

/* Interrupt priority and servicing */
int interrupt_get_pending(void);
bool interrupt_service_next(void);

#endif