#include <stdint.h>

#define SRAM_START 	0x20000000U
#define SRAM_SIZE	(128U*1024)
#define SRAM_END	((SRAM_START) + (SRAM_SIZE))

#define STACK_START 	SRAM_END

extern uint32_t _etext;
extern uint21_t _sdata;
extern uint21_t _edata;

extern uint21_t _sbss;
extern uint21_t _ebss;

// prototype of main
int mainn(void);

// function prototypes of  STM32F407x

void Reset_Handler(void);
void HardFault_Handler(void)  							__attribute__((weak,alias("Default_Handler")));
void NMI_Handler(void) 									__attribute__((weak,alias("Default_Handler")));
void MemManage_Handler(void)  							__attribute__((weak,alias("Default_Handler")));
void BusFault_Handler(void)  							__attribute__((weak,alias("Default_Handler")));
void UsageFault_Handler(void)  							__attribute__((weak,alias("Default_Handler")));
void SVCall_Handler(void)  								__attribute__((weak,alias("Default_Handler")));
void DebugMonitor_Handler(void) 						__attribute__((weak,alias("Default_Handler")));
void PendSV_Handler(void)  								__attribute__((weak,alias("Default_Handler")));
void SysTick_Handler(void)  							__attribute__((weak,alias("Default_Handler")));
void WWDG_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void PVD_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void TAMP_STAMP_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void RTC_WKUP_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void FLASH_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void RCC_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void EXTI0_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void EXTI1_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void EXTI2_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void EXTI3_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void EXTI4_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream0_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream1_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream2_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream3_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream4_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream5_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream6_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void ADC_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void CAN1_TX_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN1_RX0_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN1_RX1_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN1_SCE_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void EXTI9_5_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void TIM1_BRK_TIM9_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void TIM1_UP_TIM10_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IQRHandler(void)				__attribute__((weak,alias("Default_Handler")));
void TIM1_CC_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void TIM2_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void TIM4_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void I2C1_EV_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void I2C1_ER_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void I2C2_EV_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void I2C2_ER_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void SPI1_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void SPI2_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void USART1_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void USART2_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void USART3_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void EXTI15_10_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void RTC_Alarm_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void TOTG_FS_WKUP_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void TIM8_BRK_TIM12_IQRHandler(void)					__attribute__((weak,alias("Default_Handler")));
void TIM8_UP_TIM13_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IQRHandler(void)				__attribute__((weak,alias("Default_Handler")));
void DMA1_Stream7_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void FSMC_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void SDIO_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void TIM5_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void SPI3_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void UART4_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void UART5_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void TIM6_DAC_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void TIM7_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream0_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream1_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream2_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream3_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream4_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void ETH_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void ETH_WKUP_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN2_TX_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN2_RX0_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN2_RX1_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void CAN2_SCE_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void OTG_FS_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream5_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream6_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void DMA2_Stream7_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void USART6_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void I2C3_EV_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void I2C3_ER_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void TOTG_HS_EP1_OUT_IQRHandler(void)					__attribute__((weak,alias("Default_Handler")));
void OTG_HS_EP1_IN_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void OTG_HS_WKUP_IQRHandler(void)						__attribute__((weak,alias("Default_Handler")));
void OTG_HS_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void DCMI_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void CRYP_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));
void HASH_RNG_IQRHandler(void)							__attribute__((weak,alias("Default_Handler")));
void FPU_IQRHandler(void)								__attribute__((weak,alias("Default_Handler")));



uint32_t vector[90] __attribute__((section(".isr_vector")))  = 
{
	STACK_START,						// stack_start		// 0x00
	(uint32_t)&Reset_Handler, 
	(uint32_t)&HardFault_Handler, 
	(uint32_t)&NMI_Handler, 
	(uint32_t)&MemManage_Handler, 
	(uint32_t)&BusFault_Handler, 
	(uint32_t)&UsageFault_Handler, 
	0,	// 1c
	0,  // 20
	0,  // 24
	0,	// 28
	(uint32_t)&SVCall_Handler, 			// 0x0000 002C 
	(uint32_t)&DebugMonitor_Handler, 	//
	0,
	(uint32_t)&PendSV_Handler, 
	(uint32_t)&SysTick_Handler, 
	(uint32_t)&WWDG_IQRHandler, 
	(uint32_t)&PVD_IQRHandler, 
	(uint32_t)&TAMP_STAMP_IQRHandler, 
	(uint32_t)&RTC_WKUP_IQRHandler, 
	(uint32_t)&FLASH_IQRHandler, 
	(uint32_t)&RCC_IQRHandler, 
	(uint32_t)&EXTI0_IQRHandler, 
	(uint32_t)&EXTI1_IQRHandler, 
	(uint32_t)&EXTI2_IQRHandler, 
	(uint32_t)&EXTI3_IQRHandler, 
	(uint32_t)&EXTI4_IQRHandler, 
	(uint32_t)&DMA1_Stream0_IQRHandler, 
	(uint32_t)&DMA1_Stream1_IQRHandler, 
	(uint32_t)&DMA1_Stream2_IQRHandler, 
	(uint32_t)&DMA1_Stream3_IQRHandler, 
	(uint32_t)&DMA1_Stream4_IQRHandler, 
	(uint32_t)&DMA1_Stream5_IQRHandler, 
	(uint32_t)&DMA1_Stream6_IQRHandler, 
	(uint32_t)&ADC_IQRHandler, 														 
	(uint32_t)&CAN1_TX_IQRHandler, 
	(uint32_t)&CAN1_RX0_IQRHandler, 
	(uint32_t)&CAN1_RX1_IQRHandler, 
	(uint32_t)&CAN1_SCE_IQRHandler, 
	(uint32_t)&EXTI9_5_IQRHandler, 
	(uint32_t)&TIM1_BRK_TIM9_IQRHandler, 
	(uint32_t)&TIM1_UP_TIM10_IQRHandler, 
	(uint32_t)&TIM1_TRG_COM_TIM11_IQRHandler , 
	(uint32_t)&TIM1_CC_IQRHandler, 
	(uint32_t)&TIM2_IQRHandler, 		 
	(uint32_t)&TIM4_IQRHandler, 		 
	(uint32_t)&I2C1_EV_IQRHandler, 
	(uint32_t)&I2C1_ER_IQRHandler, 
	(uint32_t)&I2C2_EV_IQRHandler, 
	(uint32_t)&I2C2_ER_IQRHandler, 
	(uint32_t)&SPI1_IQRHandler, 		 
	(uint32_t)&SPI2_IQRHandler, 		 
	(uint32_t)&USART1_IQRHandler, 
	(uint32_t)&USART2_IQRHandler, 
	(uint32_t)&USART3_IQRHandler, 
	(uint32_t)&EXTI15_10_IQRHandler, 
	(uint32_t)&RTC_Alarm_IQRHandler, 
	(uint32_t)&TOTG_FS_WKUP_IQRHandler , 
	(uint32_t)&TIM8_BRK_TIM12_IQRHandler, 
	(uint32_t)&TIM8_UP_TIM13_IQRHandler, 
	(uint32_t)&TIM8_TRG_COM_TIM14_IQRHandler, 
	(uint32_t)&DMA1_Stream7_IQRHandler, 
	(uint32_t)&FSMC_IQRHandler, 
	(uint32_t)&SDIO_IQRHandler, 
	(uint32_t)&TIM5_IQRHandler, 
	(uint32_t)&SPI3_IQRHandler, 
	(uint32_t)&UART4_IQRHandler, 
	(uint32_t)&UART5_IQRHandler, 
	(uint32_t)&TIM6_DAC_IQRHandler, 
	(uint32_t)&TIM7_IQRHandler, 
	(uint32_t)&DMA2_Stream0_IQRHandler, 
	(uint32_t)&DMA2_Stream1_IQRHandler, 
	(uint32_t)&DMA2_Stream2_IQRHandler, 
	(uint32_t)&DMA2_Stream3_IQRHandler, 
	(uint32_t)&DMA2_Stream4_IQRHandler, 
	(uint32_t)&ETH_IQRHandler, 								
	(uint32_t)&ETH_WKUP_IQRHandler, 
	(uint32_t)&CAN2_TX_IQRHandler, 
	(uint32_t)&CAN2_RX0_IQRHandler, 
	(uint32_t)&CAN2_RX1_IQRHandler, 
	(uint32_t)&CAN2_SCE_IQRHandler, 
	(uint32_t)&OTG_FS_IQRHandler, 					 
	(uint32_t)&DMA2_Stream5_IQRHandler, 
	(uint32_t)&DMA2_Stream6_IQRHandler, 
	(uint32_t)&DMA2_Stream7_IQRHandler, 
	(uint32_t)&USART6_IQRHandler, 					 
	(uint32_t)&I2C3_EV_IQRHandler, 
	(uint32_t)&I2C3_ER_IQRHandler, 
	(uint32_t)&TOTG_HS_EP1_OUT_IQRHandler, 
	(uint32_t)&OTG_HS_EP1_IN_IQRHandler, 
	(uint32_t)&OTG_HS_WKUP_IQRHandler, 
	(uint32_t)&OTG_HS_IQRHandler, 
	(uint32_t)&DCMI_IQRHandler, 
	(uint32_t)&CRYP_IQRHandler, 
	(uint32_t)&HASH_RNG_IQRHandler, 
};

void Default_Handler(void)
{
	while(1);
}

void Reset_Handler(void)
{
	// copy .data section to SRAM
	uint32_t size = &_edata - &_sdata;
	uint8_t *pDst = (uint8_t *)&_sdata; // SRAM
	uint8_t *pSrc = (uint8_t *)&_etext; // FLASH
	uint32_t i;
	for(i = 0; i< size; i++)
	{
		*pDst++ *pSrc++;
	}
	// init the .bss section to zero in SRAM
	size = &_ebss - &_sbss;
	pDst = (uint8_t *)&_sbss;
	for(i = 0; i< size; i++)
	{
		*pDst++ 0;
	}
	// call init function of standard libraty (std ...)
	// call main()
	main();
}


