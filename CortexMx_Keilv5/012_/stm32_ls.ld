ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx):ORIGIN = 0x80000000 , LENGTH = 124K
    SRAM(rwx):ORIGIN = 0x20000000 , LENGTH = 128K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.tex)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > FLASH AT >FLASH

    .data :
    {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT >FLASH
    
    .bss :
    {
        _sbss = .;
        *(.bss) 
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM AT >SRAM
}