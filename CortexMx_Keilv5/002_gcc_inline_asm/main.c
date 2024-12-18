#include "stm32f4xx.h"                  // Device header
#include "stdint.h"

// naked gcc_inline_function
void asm_inline_funct(int a);



int main(void)
{
	int result = 0;
	asm_inline_funct(16);
	__ASM volatile("mov %0, r0"::"r"(result):);
	while(1)
	{
		
	}
	// return 0;
}


void asm_inline_funct(int a)
{
	// naked function not allow
	__ASM volatile ("ASR %0, #2":"=r"(a)::);
}
