#ifndef __SYSTICKTIMER_H
#define __SYSTICKTIMER_H 

#include "stdint.h"

/* settup systick timer */
#define STICK_HZ 					1000U
#define HSI_CLK 					16000000U
#define SYSTICK_TIM_CLK		HSI_CLK

#define Tick_us						1u
#define Tick_ms						1000U

void init_systick_timer(uint32_t Tick);

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif
