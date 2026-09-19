#include <stdio.h>
#include "register.h"
#include "timer.h"
#include "interrupt.h"

int main(void)
{
    printf("--- Microcontroller Register Simulator ---\n\n");

    /* ================= GPIO TESTS ================= */

   

    /* ================= UART TX TESTS ================= */

    /*printf("\n--- UART TX Test ---\n");

    UART_STATUS = 0;

    printf("Initial TX Ready = %d\n",
           uart_is_tx_ready());

    bool success = uart_send_byte('A');

    printf("Sending 'A' when TX not ready = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = %u\n", UART_DATA);

    UART_STATUS |= (1U << 0);

    printf("\nTX Ready after setting flag = %d\n",
           uart_is_tx_ready());

    success = uart_send_byte('A');

    printf("Sending 'A' when TX ready = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = '%c' (0x%02X)\n",
           UART_DATA, UART_DATA);

    printf("TX Ready after sending = %d\n",
           uart_is_tx_ready());

    success = uart_send_byte('B');

    printf("Sending 'B' immediately = %s\n",
           success ? "SUCCESS" : "FAILED");

    printf("UART DATA = '%c'\n", UART_DATA);*/


    /* ================= AUTOMATIC TX COMPLETION ================= */

    /*printf("\n--- Automatic TX Completion Test ---\n");

    printf("Waiting for transmission to complete...\n");

    while (!uart_is_tx_ready())
    {
        uart_update();
    }

    printf("TX Ready after automatic completion = %d\n",
           uart_is_tx_ready());

    bool success_B_retry = uart_send_byte('B');

    printf("Retry sending 'B' status = %s\n",
           success_B_retry ? "SUCCESS" : "FAILED");

    printf("New UART_DATA contains = '%c' (0x%02X)\n",
           UART_DATA, UART_DATA);

    printf("TX Ready after sending B = %d\n",
           uart_is_tx_ready()); */


    /* ================= UART RX TEST ================= */

    /*printf("\n--- UART RX Status Test ---\n");

    UART_STATUS = 0;

    printf("RX Available = %d\n",
           uart_is_rx_data_available());

    UART_STATUS |= (1U << 1);

    printf("RX Available after setting flag = %d\n",
           uart_is_rx_data_available());*/


    /* ================= TIMER TEST ================= */

    /*printf("\n--- Timer Test ---\n");

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
           TIMER_COUNT); */


    /* ================= TIMER OVERFLOW TEST ================= */

    /*printf("\n--- Timer Overflow Test ---\n");

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
           (TIMER_STATUS & (1U << 0)) != 0);*/


    /* ================= STICKY OVERFLOW TEST ================= */

    /*printf("\n--- Sticky Overflow Test ---\n");

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
           (TIMER_STATUS & (1U << 0)) != 0);*/


    /* ================= INTERRUPT TEST ================= */

    printf("\n--- Interrupt Test ---\n");

    interrupt_init();

    printf("Initial INT_ENABLE = %u\n",
           INT_ENABLE);

    interrupt_int0_enable();

    printf("INT_ENABLE after enabling INT0 = %u\n",
           INT_ENABLE);

    interrupt_int0_disable();

    printf("INT_ENABLE after disabling INT0 = %u\n",
           INT_ENABLE);


    /* ================= INTERRUPT TRIGGER TEST ================= */

    printf("\n--- Interrupt Trigger Test ---\n");

    interrupt_init();

    printf("Initial INT_PENDING = %u\n",
           INT_PENDING);

    interrupt_int0_trigger();

    printf("INT_PENDING after INT0 trigger = %u\n",
           INT_PENDING);


    /* ================= INTERRUPT CLEAR TEST ================= */

    printf("\n--- Interrupt Clear Test ---\n");

    interrupt_init();

    interrupt_int0_trigger();

    printf("INT_PENDING after trigger = %u\n",
           INT_PENDING);

    interrupt_int0_clear();

    printf("INT_PENDING after clear = %u\n",
           INT_PENDING);


    /* ================= TIMER TO INTERRUPT TEST ================= */

    printf("\n--- Timer to Interrupt Test ---\n");

    TIMER_COUNT = 255;
    TIMER_CONTROL = 0;
    TIMER_STATUS = 0;

    interrupt_init();

    timer_start();

    printf("INT_PENDING before timer update = %u\n",
           INT_PENDING);

    timer_update();

    printf("Timer Count after overflow = %u\n",
           TIMER_COUNT);

    printf("Timer Overflow Flag = %d\n",
           (TIMER_STATUS & (1U << 0)) != 0);

    printf("INT_PENDING after timer overflow = %u\n",
           INT_PENDING);


    /* ================= INTERRUPT SERVICE TEST ================= */

    printf("\n--- Interrupt Service Test ---\n");

    interrupt_init();

    interrupt_int0_enable();
    interrupt_int0_trigger();

    printf("INT_PENDING before service = %u\n",
           INT_PENDING);

    bool serviced = interrupt_service_int0();

    printf("Interrupt serviced = %s\n",
           serviced ? "YES" : "NO");

    printf("INT_PENDING after service = %u\n",
           INT_PENDING);


    /* ================= INTERRUPT NEGATIVE TESTS ================= */

    printf("\n--- Interrupt Service Negative Tests ---\n");

    /* Case 1: Interrupt disabled but pending */

    interrupt_init();

    interrupt_int0_trigger();

    serviced = interrupt_service_int0();

    printf("Case 1 - Disabled + Pending: %s\n",
           serviced ? "YES" : "NO");

    printf("INT_PENDING = %u\n",
           INT_PENDING);


    /* Case 2: Interrupt enabled but not pending */

    interrupt_init();

    interrupt_int0_enable();

    serviced = interrupt_service_int0();

    printf("Case 2 - Enabled + Not Pending: %s\n",
           serviced ? "YES" : "NO");

    printf("INT_PENDING = %u\n",
           INT_PENDING);


    
    /* ================= INT1 TEST ================= */

    printf("\n--- INT1 Test ---\n");

    interrupt_init();

    printf("Initial INT_ENABLE = %u\n", INT_ENABLE);

    interrupt_int1_enable();

    printf("INT_ENABLE after enabling INT1 = %u\n",
           INT_ENABLE);

    interrupt_int1_trigger();

    printf("INT_PENDING after triggering INT1 = %u\n",
           INT_PENDING);

    interrupt_int1_clear();

    printf("INT_PENDING after clearing INT1 = %u\n",
           INT_PENDING);

    interrupt_int1_disable();

    printf("INT_ENABLE after disabling INT1 = %u\n",
           INT_ENABLE);
    
    /* ================= INTERRUPT PRIORITY TEST ================= */

    printf("\n--- Interrupt Priority Test ---\n");

    interrupt_init();

/* Enable both interrupts */
    interrupt_int0_enable();
    interrupt_int1_enable();

/* Trigger both interrupts */
    interrupt_int0_trigger();
    interrupt_int1_trigger();

    printf("INT_ENABLE = %u\n", INT_ENABLE);
    printf("INT_PENDING = %u\n", INT_PENDING);

    printf("Next interrupt to service = %d\n",
            interrupt_get_pending()); 
    /* ================= INT1 SERVICE TEST ================= */

    printf("\n--- INT1 Service Test ---\n");

    interrupt_init();

    interrupt_int1_enable();
    interrupt_int1_trigger();

    printf("INT_PENDING before INT1 service = %u\n",
           INT_PENDING);

    bool serviced_int1 = interrupt_service_int1();

    printf("INT1 serviced = %s\n",
           serviced_int1 ? "YES" : "NO");

    printf("INT_PENDING after INT1 service = %u\n",
           INT_PENDING); 
    /* ================= INTERRUPT SERVICE NEXT TEST ================= */

    printf("\n--- Interrupt Service Next Test ---\n");

    interrupt_init();

    interrupt_int0_enable();
    interrupt_int1_enable();

    interrupt_int0_trigger();
    interrupt_int1_trigger();

    printf("Initial INT_ENABLE = %u\n", INT_ENABLE);
    printf("Initial INT_PENDING = %u\n", INT_PENDING);

/* First service: INT0 should win */
    bool serviced_next = interrupt_service_next();

    printf("First interrupt serviced = %s\n",
           serviced_next ? "YES" : "NO");

    printf("INT_PENDING after first service = %u\n",
           INT_PENDING);

/* Second service: INT1 should now be serviced */
    serviced_next = interrupt_service_next();

    printf("Second interrupt serviced = %s\n",
           serviced_next ? "YES" : "NO");

    printf("INT_PENDING after second service = %u\n",
           INT_PENDING);

/* Third service: nothing should remain */
    serviced_next = interrupt_service_next();

    printf("Third interrupt serviced = %s\n",
           serviced_next ? "YES" : "NO");

    printf("INT_PENDING after third service = %u\n",
           INT_PENDING);  
    printf("\n--- All Tests Completed ---\n");                      
    return 0;
}    