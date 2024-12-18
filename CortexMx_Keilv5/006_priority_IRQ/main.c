#include "stm32f4xx.h"                  // Device header
#include "stdint.h"

void I2C1_EV_IRQHandler(void);
void TIM2_IRQHandler(void);
void configure_priority_for_irqs(uint8_t irq_no, uint8_t prio_value);

#define IRQNO_TIMER2 	28
#define IRQNO_I2C1		31

static uint32_t *pNIVC_ISE_Base = (uint32_t*) 0xE000E100;
static uint32_t *pNIVC_IPR_Base = (uint32_t*) 0xE000E400;
static uint32_t *pNIVC_ISPR_Base = (uint32_t*) 0xE000E200;

int main(void)
{
	// configure the priority for the peripherals
	configure_priority_for_irqs(IRQNO_TIMER2, 0x60);
	configure_priority_for_irqs(IRQNO_I2C1, 0x80);
	// set the interrupt pending bit in the NVIC PR
	*pNIVC_ISPR_Base |= (1<<IRQNO_TIMER2);
//	*pNIVC_ISPR_Base |= (uint32_t)(1<<IRQNO_I2C1);
	// enable the IRQs in NVIC ISER
	*pNIVC_ISE_Base |= ((uint32_t)1<<IRQNO_I2C1);
	*pNIVC_ISE_Base |= (uint32_t)(1<<IRQNO_TIMER2);
	
}

void configure_priority_for_irqs(uint8_t irq_no, uint8_t prio_value)
{
	// find our irqx
	// find possition in iqrx
	uint8_t irqx = irq_no/4;
	uint32_t*irq = pNIVC_IPR_Base + irqx;
	uint8_t irq_pos = (irq_no % 4) * 8 ;
	// configure the priority
	*irq &= (uint32_t)~(0xff << irq_pos);
	*irq |= (uint32_t)(prio_value << irq_pos);
}

void I2C1_EV_IRQHandler(void)
{

}
void TIM2_IRQHandler(void)
{
	*pNIVC_ISE_Base |= ((uint32_t)1<<IRQNO_I2C1);
	while(1);
}
