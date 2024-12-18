#ifndef __BIT_BAND_H
#define __BIT_BAND_H

#define BIT_BAND_PERIPERAL_BASE 0x40000000U
#define BIT_BAND_SRAM_BASE		0x20000000U
#define ALIAS_PERIPERAL_BASE	0x42000000U
#define ALIAS_SRAM_BASE			0x22000000U

#define ALIAS_SRAM_ADDRESS(SRAM_Address, bit_x)           (ALIAS_SRAM_BASE + (32 *((SRAM_Address) - BIT_BAND_SRAM_BASE)) + (bit_x)*4)
#define ALIAS_PERIPERAL_ADDRESS(PERI_Address, bit_x)      (ALIAS_PERIPERAL_BASE + (32 *((PERI_Address) - BIT_BAND_PERIPERAL_BASE)) + (bit_x)*4)

#define ALIAS_SRAM_POINTER(SRAM_Address, bit_x)           (uint8_t *)ALIAS_SRAM_ADDRESS(SRAM_Address, bit_x)
#define ALIAS_PERIPERAL_POINTER(PERI_Address, bit_x)      (uint8_t *)ALIAS_PERIPERAL_ADDRESS(PERI_Address, bit_x)

//#define BIT_BAND_SRAM_SET_BIT(SRAM_Address)
//PERIPERAL

// #define SET_BIT(Addr, bit) 

#endif
