/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// this function executes in Thread Mode of the processor
void generate_interrupt()
{
	uint32_t *pSTIR =(uint32_t *)0xE000EF00;
	uint32_t *pISER0 = (uint32_t *)0xE000E100;

	// enable IRQ3 interrupt
	*pISER0 |= (1<<3);

	// generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);
}

void change_access_level_unpriv()
{
	// Read CONTROL register
	__asm volatile ("MRS R0,CONTROL"); // R0 = CONTROL
	// Modify the value of CONTROL register
	__asm volatile ("ORR R0, R0, #0x01"); // R0 = R0&0x01;
	// Load the value in to CONTROL register
	__asm volatile ("MSR CONTROL, R0"); // CONTROL = R0
}

// function exercutes in Thread Mode  of the processor
int main(void)
{
	// printf("In Thread Mode : before interrupt\n");

//	access level change : PAL -> N-PAL
	change_access_level_unpriv();

	generate_interrupt();
	// printf("In Thread Mode : before interrupt\n");
    /* Loop forever */
	while(1);
}

// this function(ISR) executes in Handler Mode of the processor
void RTC_WKUP_IRQHandler(void)
{
	// printf("In handler mode : ISR");
}

void HardFault_Handler(void)
{
	// printf("Hard Fault detected\n");
	while(1);
}
