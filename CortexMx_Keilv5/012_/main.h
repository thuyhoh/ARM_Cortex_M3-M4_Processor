#ifndef __MAIN_H
#define __MAIN_H

//#include "stm32f4xx.h"                  // Device header
#include "stdint.h"
#include "led.h"

#define MAX_TASK 5

#define STICK_HZ 					1000U
#define HSI_CLK 					16000000U
#define SYSTICK_TIM_CLK		HSI_CLK

#define INTERRUPT_DISABLE()  do{__asm volatile ("MOV R0,#0x1"); __asm volatile("MSR PRIMASK,R0"); } while(0)

#define INTERRUPT_ENABLE()  do{__asm volatile ("MOV R0,#0x0"); __asm volatile("MSR PRIMASK,R0"); } while(0)	

void enable_processor_faults(void);

/* handler function */
void init_systick_timer(uint32_t Tick);
void SysTick_Handler(void);
void PendSV_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler (void);         
void BusFault_Handler  (void);        
void UsageFault_Handler(void); 

/* Task function */
void idle_task(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void update_next_task(void);
void schedule(void);
void task_delay(uint32_t tick_count);

/* Some stack memory calculations */
#define SIZE_STASK_STACK 		1024U
#define SIZE_SCHED_STACK		1024U

#define SRAM_START					0x20000000U
#define SIZE_SRAM						((128)*(1024))
#define SRAM_END						SRAM_START + SIZE_SRAM

#define T1_STACK_START			SRAM_END
#define T2_STACK_START			(SRAM_END - (1* (SIZE_STASK_STACK)))
#define T3_STACK_START			(SRAM_END - (2* (SIZE_STASK_STACK)))
#define T4_STACK_START			(SRAM_END - (3* (SIZE_STASK_STACK)))
#define IDLE_STACK_START		(SRAM_END - (4* (SIZE_STASK_STACK)))
#define SCHED_STACK_START		(SRAM_END - (5* (SIZE_STASK_STACK)))

/*Stack function*/
uint32_t get_PSP_value(void);
__attribute__((naked)) void witch_sp_to_PSP(void);
void save_PSP_value(uint32_t current_PSP_value);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);

void update_global_tick_count(void);
void unlock_tasks(void);


#define DUMMY_XPSR          0x01000000U

typedef struct Task_Control_Block
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	void (*task_handler)(void);
}TCB_t;

#define TASK_READY_STATE 0x00
#define TASK_BLOCK_STATE  0xFF

void init_tasks_stack(void);



#endif
