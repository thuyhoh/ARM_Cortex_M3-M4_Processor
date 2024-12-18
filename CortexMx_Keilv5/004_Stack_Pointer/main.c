#include "stm32f4xx.h"                  // Device header
#include "stdint.h"

__attribute__((naked)) void change_sp2psp(void);
void generate_interrupt(void);
void SVC_Handler(void);
void HardFault_Handler(void);

int main(void)
{
	change_sp2psp();
	
	generate_interrupt();
	
	while(1)
	{}
	//return 0;
}

__attribute__((naked)) void change_sp2psp(void)
{
	__asm volatile (".equ SRAM_END, (0x20000000+(128 + 1024))");
	__asm volatile (".equ PSP_START, (SRAM_END - 512)");
	__asm volatile ("LDR R0, =PSP_START");
	__asm volatile ("MSR PSP, R0");
	__asm volatile ("MOV R0, #0x02");
	__asm volatile ("MSR CONTROL, R0");
	__asm volatile ("Bx LR");
}

void generate_interrupt(void)
{
	__ASM volatile ("SVC #0x2");
}

// this function(ISR) executes in Handler Mode of the processor
void SVC_Handler(void)
{
	// printf("In handler mode : ISR");
}

