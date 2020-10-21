#include "contiki.h"
#include "sys/clock.h"
#include "sys/etimer.h"

/*---------------------------------------------------------------------------*/
/**
 * \brief Arch-specific implementation of clock_init for the stm32l031
 *
 * We initialise the SysTick to fire 128 interrupts per second, giving us a
 * value of 128 for CLOCK_SECOND
 *
 * We also initialise GPT0:Timer A, which is used by clock_delay_usec().
 * We use 16-bit range (individual), count-down, one-shot, no interrupts.
 * The prescaler is computed according to the system clock in order to get 1
 * tick per usec.
 */
void
clock_init(void)
{
    SysTick_Config();
}