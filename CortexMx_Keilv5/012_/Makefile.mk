CC = arm-none-eabi-gcc
MACH = cortex-m4
# $(MACH) -> replace by the value of MACH
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0

# main.o -> target ($@)
# main.c -> dependences ($^)

all: main.o led.o stm32_startupt.o

main.o:main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 main.c -o main.o
# arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 main.c -o main.o

# arm-none-eabi-objdump.exe

led.o:led.c
    arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 led.c -o led.o

Systick_Timer.o:Systick_Timer.c
    arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 Systick_Timer.c -o Systick_Timer.o

stm32_startup.o:stm32_startup.c
    arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 stm32_startup.c -o stm32_startup.o

final.elf:
    arm-none-eabi-gcc -nostdlib -T stm32_ls.ld -Wl,-Map=final.map -o final.elf *o

clean: 
	rm -rf *.o *.elf

# 
