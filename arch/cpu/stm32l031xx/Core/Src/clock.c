#include "contiki.h"
#include "sys/clock.h"
#include "sys/etimer.h"

#include "stm32l031xx-conf.h"
#include "stm32l031xx-def.h"

#include "stm32l0xx.h"

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
    SysTick_Config(STM32L031_SYSCLK/CLOCK_CONF_SECOND);

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