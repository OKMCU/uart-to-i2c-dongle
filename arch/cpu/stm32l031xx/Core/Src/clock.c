#include "contiki.h"
#include "sys/clock.h"
#include "sys/etimer.h"
#include "cm0plus/cm0plus-def.h"

#include "main.h"

static volatile uint32_t tick;
static volatile uint32_t seconds;
/*---------------------------------------------------------------------------*/
/**
 * \brief Arch-specific implementation of clock_init for the stm32l031
 *
 * We initialise the SysTick to fire 128 interrupts per second, giving us a
 * value of 128 for CLOCK_SECOND
 *
 * We also initialise TIM2, which is used by clock_delay_usec().
 * We use 16-bit range (individual), count-down, one-shot, no interrupts.
 * The prescaler is computed according to the system clock in order to get 1
 * tick per usec.
 */
void
clock_init(void)
{
    tick = 0;

    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    SysTick_Config(STM32L031_SYSCLK/CLOCK_SECOND);

    // Init Timer 2 for precise delay purpose
    LL_APB1_GRP1_EnableClock( LL_APB1_GRP1_PERIPH_TIM2 );
    LL_TIM_SetClockDivision( TIM2, LL_TIM_CLOCKDIVISION_DIV1 );
    LL_TIM_DisableARRPreload( TIM2 );
    LL_TIM_SetCounterMode( TIM2, LL_TIM_COUNTERMODE_DOWN );
    LL_TIM_SetOnePulseMode( TIM2, LL_TIM_ONEPULSEMODE_SINGLE );
    LL_TIM_SetUpdateSource( TIM2, LL_TIM_UPDATESOURCE_COUNTER );
    LL_TIM_DisableUpdateEvent( TIM2 );
    LL_TIM_SetPrescaler( TIM2, 0 );
}

/**
 * Get the current clock time.
 *
 * This function returns the current system clock time.
 *
 * \return The current clock time, measured in system ticks.
 */
clock_time_t
clock_time(void)
{
    return tick;
}

/**
 * Get the current value of the platform seconds.
 *
 * This could be the number of seconds since startup, or
 * since a standard epoch.
 *
 * \return The value.
 */
unsigned long
clock_seconds(void)
{

}

/**
 * Set the value of the platform seconds.
 * \param sec   The value to set.
 *
 */
void
clock_set_seconds(unsigned long sec)
{

}

/**
 * Wait for a given number of ticks.
 * \param t   How many ticks.
 *
 */
void
clock_wait(clock_time_t t)
{

}

/**
 * Delay a given number of microseconds.
 * \param dt   How many microseconds to delay.
 *
 * \note Interrupts could increase the delay by a variable amount.
 */
void
clock_delay_usec(uint16_t dt)
{

}

/**
  * \brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
    tick++;
    if (etimer_pending()) {
        etimer_request_poll();
    }
}