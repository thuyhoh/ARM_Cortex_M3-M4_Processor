#include "stm32f4xx.h"                  // Device header
#include "stdint.h"
#include "stdio.h"
/*
Write a program to execute an SVC instruction from thread mode,
implement the svc handler to print the SVC number used.
Also,  increment the SVC number by 4 and return it to the thread mode code and print it.
Hints :
1)Write a main() function where you should execute the SVC instruction with an argument.
let's say SVC #0x5
2)Implement the SVC handler
3)In the SVC handler extract the SVC number and print it using printf
4) Increment the SVC number by 4 and return it to the thread mode
*/

void SVC_Handler(void);
void SVC_Handler_c(uint32_t *pBaseOfStackFrame);


int main(void)
{
	__ASM("SVC #0x12");
	uint32_t data;
	__asm volatile ("MOV %0,R0": "=r"(data) ::);
	
//	printf("%d",data);
	while(1)
	{}
//	return 0;
}


//1 . get the value of the MSP
__attribute__((naked)) void SVC_Handler(void)
{
	__asm("MRS r0,MSP");
	__asm("B SVC_Handler_c");
}

__attribute__((noreturn)) void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
	uint8_t *pReturn_addr = (uint8_t *)pBaseOfStackFrame[6];
	//2. decrement the return address by 2 to point to opcode of the SVC instruction in the program memory
	pReturn_addr -= 2;
	//3. extract the SVC number (LSByte of the opcode)
	uint8_t svc_num =  *pReturn_addr;
//	printf("svc %d\n",svc_num);
	svc_num += 4;
	pBaseOfStackFrame[0] = svc_num;
}
