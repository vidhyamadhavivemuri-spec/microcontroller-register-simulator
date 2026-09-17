#include "interrupt.h"
#include "register.h"

void interrupt_init(void)
{
    INT_ENABLE = 0;
    INT_PENDING = 0;
}

void interrupt_int0_enable(void)
{
    INT_ENABLE |= INT0_BIT_MASK;
}

void interrupt_int0_disable(void)
{
    INT_ENABLE &= ~INT0_BIT_MASK;
}

void interrupt_int0_trigger(void)
{
    INT_PENDING |= INT0_BIT_MASK;
}

void interrupt_int0_clear(void)
{
    INT_PENDING &= ~INT0_BIT_MASK;
}

bool interrupt_int0_is_pending_and_enabled(void)
{
    return (INT_ENABLE & INT0_BIT_MASK) &&
           (INT_PENDING & INT0_BIT_MASK);
}

bool interrupt_service_int0(void)
{
    if (interrupt_int0_is_pending_and_enabled())
    {
        interrupt_int0_clear();
        return true;
    }

    return false;
}
void interrupt_int1_enable(void)
{
    INT_ENABLE |= INT1_BIT_MASK;
}

void interrupt_int1_disable(void)
{
    INT_ENABLE &= ~INT1_BIT_MASK;
}

void interrupt_int1_trigger(void)
{
    INT_PENDING |= INT1_BIT_MASK;
}

void interrupt_int1_clear(void)
{
    INT_PENDING &= ~INT1_BIT_MASK;
}
int interrupt_get_pending(void)
{
    if ((INT_ENABLE & INT0_BIT_MASK) &&
        (INT_PENDING & INT0_BIT_MASK))
    {
        return 0;
    }

    if ((INT_ENABLE & INT1_BIT_MASK) &&
        (INT_PENDING & INT1_BIT_MASK))
    {
        return 1;
    }

    return -1;
}
bool interrupt_service_int1(void)
{
    if ((INT_ENABLE & INT1_BIT_MASK) &&
        (INT_PENDING & INT1_BIT_MASK))
    {
        interrupt_int1_clear();
        return true;
    }

    return false;
}
bool interrupt_service_next(void)
{
    int pending = interrupt_get_pending();

    if (pending == 0)
        return interrupt_service_int0();

    if (pending == 1)
        return interrupt_service_int1();

    return false;
}