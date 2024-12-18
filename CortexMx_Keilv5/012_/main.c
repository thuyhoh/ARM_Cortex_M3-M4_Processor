#include "main.h"

static TCB_t user_tasks[MAX_TASK];

void PendSVhandler_set_Priority(uint8_t priority);
void PendSVhandler_active(void);

static uint8_t  current_task = 1;
static uint32_t g_tick_count = 0;
int main(void)
{
	enable_processor_faults();
	
	init_scheduler_stack(SCHED_STACK_START);
	
	init_tasks_stack();
	led_init_all();
	
	init_systick_timer(STICK_HZ);
	
	witch_sp_to_PSP();
	
	task1_handler();
	
	while(1)
	{}
	// return 0;
}

void idle_task(void)
{
	while(1)
	{}
}

void enable_processor_faults(void)
{
	uint32_t *pSHCSR = (uint32_t *)0xE000ED24;
	*pSHCSR |= (1<<16); // mem manage
	*pSHCSR |= (1<<17); // bus fault
	*pSHCSR |= (1<<18); // usage fault
}

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack)
{
	__asm volatile ("MSR MSP, R0"); // r0 stored the value of sched_top_of_stack
	__asm volatile ("BX LR");				// back to main function
}

void init_tasks_stack(void)
{
	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	
	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;
	
	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;
	
	uint16_t i, j;
	uint32_t *pPSP;
	for(i = 0; i < MAX_TASK; i++)
	{
		pPSP = (uint32_t *)user_tasks[i].psp_value;
		pPSP--;
		*pPSP = DUMMY_XPSR; 					// xPSR
		pPSP--;
		*pPSP = (uint32_t)user_tasks[i].task_handler; 			// PC
		pPSP--;
		*pPSP = 0xFFFFFFFD;						// LR
		for(j = 0; j <13; j++)
		{
			pPSP--;											
			*pPSP = 0;									// Rx
		}
		user_tasks[i].psp_value = (uint32_t)pPSP;
	}
	
}
uint32_t get_PSP_value(void)
{
	return user_tasks[current_task].psp_value;
}

void update_next_task(void)
{
	uint16_t i;
	uint8_t state = TASK_BLOCK_STATE;
	for(i = 0; i< (MAX_TASK); i++)
	{
		current_task++;
		current_task = current_task % MAX_TASK;
		state = user_tasks[current_task].current_state;
		if((state == TASK_READY_STATE) && (current_task != 0)) break;
	}
	if(state != TASK_READY_STATE) current_task = 0;
}

void save_PSP_value(uint32_t current_PSP_value)
{
	user_tasks[current_task].psp_value = current_PSP_value;
}

__attribute__((naked)) void witch_sp_to_PSP(void)
{
	// 1 init the PSP with TASK1 start address
	__asm volatile ("PUSH {LR}");				 // preserve LR which connect back to main()
	__asm volatile ("BL get_PSP_value");
	__asm volatile ("MSR PSP, R0");		 // Initialize PSP
	__asm volatile ("POP {LR}");				 // pop back LR value
	
	// 2 change SP to PSP using CONTROL register
	__asm volatile ("MOV R0, #0x02");
	__asm volatile ("MSR CONTROL, R0");
	__asm volatile ("BX LR");
}

void PendSVhandler_set_Priority(uint8_t priority)
{
	uint32_t *pSHPR = (uint32_t *)0xE000ED20;
	*pSHPR |= (uint32_t)(priority<<20);
}

void PendSVhandler_active(void)
{
// active PendSV_handler
	uint32_t *pICSR = (uint32_t *)0xE000ED04;
	*pICSR |= 1<<28;
}

void update_global_tick_count(void)
{
	g_tick_count++;
}

void unlock_tasks(void)
{
	int i;
	for(i = 1; i < MAX_TASK; i++)
	{
		if(user_tasks[i].current_state != TASK_READY_STATE)
		{
			if(user_tasks[i].block_count == g_tick_count)
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
		}
	}
}

void SysTick_Handler(void)
{
	update_global_tick_count();
	unlock_tasks();	
	PendSVhandler_active();
}

void PendSV_Handler(void)
{
	/*Save the context of current task*/
	// 1. get current running task's PSP value
	__asm volatile("MRS R0, PSP");
	// 2. using that PSP value store SF2(R4-r11)
	__asm volatile("STMDB R0!, {R4- R11}");
	__asm volatile("PUSH {LR}");
	// 3. save the current value of PSP
	__asm volatile("BL save_PSP_value");
	
	/* retrieve the context of next task*/
	// 1. Decide next task to run
	__asm volatile("BL update_next_task");
	// 2. get its past PSP value
	__asm volatile("BL get_PSP_value");
	// 3. using that PSP value retrieve SP2(R4- R11)
	__asm volatile ("POP {LR}");
	__asm volatile("LDMIA R0!, {R4-R11}");
	// 4. upadate PSP and exit
	__asm volatile ("MSR PSP, R0");
	__asm volatile ("BX LR");
}

void schedule(void)
{
	PendSVhandler_active();
}

void task_delay(uint32_t tick_count)
{
	// disable interrupt
	INTERRUPT_DISABLE();
	if(current_task)
	{
		user_tasks[current_task].block_count = g_tick_count + tick_count;
		user_tasks[current_task].current_state = TASK_BLOCK_STATE;
		schedule();
	}
	
	// enable interrupt
	INTERRUPT_ENABLE();
}

void task1_handler(void)
{
	while(1)
	{
		led_on(LED_ORANGE);
		delay(DELAY_COUNT_500MS);
		led_off(LED_ORANGE);
		delay(DELAY_COUNT_500MS);
	}
}
void task2_handler(void)
{
	while(1)
	{
		led_on(LED_BLUE);
		delay(DELAY_COUNT_250MS);
		led_off(LED_BLUE);
		delay(DELAY_COUNT_250MS);
	}
}
void task3_handler(void)
{
	while(1)
	{
		led_on(LED_RED);
		delay(DELAY_COUNT_125MS);
		led_off(LED_RED);
		delay(DELAY_COUNT_125MS);
	}
}
void task4_handler(void)
{
	while(1)
	{
		led_on(LED_GREEN);
		delay(DELAY_COUNT_1S);
		led_off(LED_GREEN);
		delay(DELAY_COUNT_1S);
	}
}

void init_systick_timer(uint32_t Tick)
{
	uint32_t *pSCSR = (uint32_t *)0xE000E010;
	uint32_t *pSRVR = (uint32_t *)0xE000E014;

	uint32_t count_value = (SYSTICK_TIM_CLK/Tick) - 1;
	
	// Clear the value of SRVR
	*pSRVR &= ~(0x00FFFFFFFF);
	// load the value into SRVR
	*pSRVR |= count_value;
	
	// setting SCSR
	*pSCSR |= (1<<2); // indicates the clock soures, processor clock source
	*pSCSR |= (1<<1); // enable SysTick exception request
	// enable the Systick
	*pSCSR |= (1<<0);
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

void UsageFault_Handler(void)
{
	
}
