#include <stdint.h>
#include <stdio.h>

int g_un_data;			//.bss
int g_i_data = 0x90; 	      	// .data
static int g_un_s_data;		// .bss
static int g_i_s_data = 0x24; 	// .data
const int g_c_data;		// .rodata

int main(void)
{
    int l_un_data;			// stack
    int l_i_data = 0x90;		// stack
    static int l_un_s_data;		// .bss
    static int l_i_s_data = 0x24;	// .data
    const int l_c_data = 0x45;		// .rodata
}
