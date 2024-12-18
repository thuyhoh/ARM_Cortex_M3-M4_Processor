#include "stm32f4xx.h"                  // Device header

#include "stdint.h"
#include "bit_band.h"

int main(void)
{
	/* Ex: 	the value of 0x20000200_addr = 0xff and clear the 7th bit  */
	uint8_t *ptr = (uint8_t *)0x20000200;
	*ptr = 0xff;

	// normal method
	*ptr &= ~(1<<7); // clearing 7th bit position

	// reset value of 0x20000200_addr
	*ptr = 0xff;
	// bit banding method
	uint8_t *alias_addr = ALIAS_SRAM_POINTER((uint32_t)ptr,6);
	
	*alias_addr = 0;// clearing 7th bit position
	/* Loop forever */
	while(1)
	{}
	// return 0;
}

