#include "stm32f4xx.h"                  // Device header
#include "stdint.h"


void SVC_Handler(void);
void SVC_Handler_c(uint32_t *pBaseOfStackFrame);
int32_t add_number(int32_t a, int32_t b);
int32_t sub_number(int32_t a, int32_t b);
int32_t mul_number(int32_t a, int32_t b);
int32_t div_number(int32_t a, int32_t b);

int32_t ans;

int main(void)
{
	int32_t a = 6, b = 8;
	ans = add_number(a, b);
	ans = sub_number(6, 8);
	ans = mul_number(6, 8);
	ans = div_number(6, 8);
	
//	printf("%d",data);
	while(1)
	{}
//	return 0;
}


int32_t add_number(int32_t a, int32_t b)
{
	int32_t res;
	__ASM volatile ("SVC #36");
	__ASM volatile ("MOV %0,r0": "=r"(res)::);
	return res;
}
int32_t sub_number(int32_t a, int32_t b)
{
	int32_t res;
	__ASM volatile ("SVC #37");
	__ASM volatile ("MOV %0,r0": "=r"(res)::);
	return res;
}
int32_t mul_number(int32_t a, int32_t b)
{
	int32_t res;
	__ASM volatile ("SVC #38");
	__ASM volatile ("MOV %0,r0": "=r"(res)::);
	return res;
}
int32_t div_number(int32_t a, int32_t b)
{
	int32_t res;
	__ASM volatile ("SVC #39");
	__ASM volatile ("MOV %0,r0": "=r"(res)::);
	return res;
}

//1 . get the value of the MSP
__attribute__((naked)) void SVC_Handler(void)
{
	__asm("MRS r0,MSP");
	__asm("B SVC_Handler_c");
}

void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
	int32_t arg0, arg1, res;
	uint8_t *pReturn_addr = (uint8_t *)pBaseOfStackFrame[6];
	//2. decrement the return address by 2 to point to opcode of the SVC instruction in the program memory
	pReturn_addr -= 2;
	//3. extract the SVC number (LSByte of the opcode)
	uint8_t svc_num =  *pReturn_addr;
//	printf("svc %d\n",svc_num);
	arg0 = (int32_t)pBaseOfStackFrame[0];
	arg1 = (int32_t)pBaseOfStackFrame[1];
	switch(svc_num)
	{
		case 36:
			res = arg0 + arg1;
			break;
		case 37:
			res = arg0 - arg1;
			break;
		case 38:
			res = arg0 * arg1;
			break;
		case 39:
			res = arg0 / arg1;
			break;
//		default:
////			printf("error");
	}
	pBaseOfStackFrame[0] = res;
}

void HardFault_Handler(void)
{
	
}
