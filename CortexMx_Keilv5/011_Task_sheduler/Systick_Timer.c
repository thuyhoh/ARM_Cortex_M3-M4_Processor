#include "Systick_Timer.h"

void init_systick_timer(uint32_t Tick)
{
	uint32_t *pSCSR = (uint32_t *)0xE000E010;
	uint32_t *pSRVR = (uint32_t *)0xE000E014;

	uint32_t count_value = (SYSTICK_TIM_CLK/Tick) - 1;
	
	// Clear the value of SRVR
	*pSRVR &= ~(0x00FFFFFFFF);
	// load the value into SRVR
	*pSRVR |= count_value;
	
	// setting SCSR
	*pSCSR |= (1<<2); // indicates the clock soures, processor clock source
	*pSCSR |= (1<<1); // enable SysTick exception request
	// enable the Systick
	*pSCSR |= (1<<0);
}

void delay_ms(uint32_t ms)
{
	while(ms--)
	{
		init_systick_timer(Tick_ms);
	}
}

void delay_us(uint32_t us)
{
	while(us--)
	{
		init_systick_timer(Tick_us);
	}
}
