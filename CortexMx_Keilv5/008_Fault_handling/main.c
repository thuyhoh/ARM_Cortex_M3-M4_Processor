#include "stm32f4xx.h"                  // Device header
#include "stdio.h"

	// 2 implement the fault handlers
void HardFault_Handler(void);
void MemManage_Handler (void);         
void BusFault_Handler  (void);        
void UsageFault_Handler(void); 
void UsageFault_Handler_c(uint32_t *pBaseStackFrame);

int main(void)
{
	// 1 enable all configurable excption
	uint32_t *pSHCSR = (uint32_t *)0xE000ED24;
	*pSHCSR |= (1<<16); // mem manage
	*pSHCSR |= (1<<17); // bus fault
	*pSHCSR |= (1<<18); // usage fault
	
	//
	uint32_t *pSRAM = (uint32_t *)0x20010000;
	*pSRAM = 0xFFFFFFFF;
	void (*some_address)(void);
	some_address = (void *)pSRAM;
	some_address(); // -> ko giai ma dc len trong dia chi pSRAM
	
	while(1)
	{
		
	}
}

void HardFault_Handler(void)
{
	
}
void MemManage_Handler (void)
{
	
}	
void BusFault_Handler  (void)
{
	
}	

__attribute__((naked)) void UsageFault_Handler(void) // caller
{
	__ASM("MRS r0,MSP");
	__asm("B UsageFault_Handler_c"); 
}

__attribute__((noreturn)) void UsageFault_Handler_c(uint32_t *pBaseStackFrame) // calle
{
	printf("address of MSP : %#x",(uint32_t)pBaseStackFrame);
	printf("value of R0: %#x",pBaseStackFrame[0]);
	printf("value of R1: %#x",pBaseStackFrame[1]);
	printf("value of R2: %#x",pBaseStackFrame[2]);
	printf("value of R3: %#x",pBaseStackFrame[3]);
	printf("value of R12: %#x",pBaseStackFrame[4]);
	printf("value of LR: %#x",pBaseStackFrame[5]);
	printf("value of PC: %#x",pBaseStackFrame[6]);
	printf("value of XPSR: %#x",pBaseStackFrame[7]);
	uint32_t *pUFSR = (uint32_t*)0xE000ED2A;
	printf("UFSR = %#x",(uint32_t)pUFSR);	
	while(1);
}	
