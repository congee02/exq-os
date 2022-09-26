#include <exqos/arch/gdt.h>
#include <stdint.h>

#define GDT_ENTRY 5

uint64_t _gdt[GDT_ENTRY];
uint16_t _gdt_limit = sizeof(_gdt) - 1;

/*
    段选择器 (作为 GDT 的 条目)
    = <Low: <Segment_Limit: [0, 15], Base_Address_L: [16, 31]>, 
       High: <Base_Address_M: [0, 7], Segment Flags: [8, 23], Base_Address_H: [24, 31] > >
    
    Segment Flag: 参考 gdt.h
*/
void _set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint32_t flags) {
    _gdt[index] = SEG_BASE_H(base) | flags | SEG_LIM_H(limit) | SEG_BASE_M(base);
    _gdt[index] <<= 32;
    _gdt[index] |= SEG_BASE_L(base) | SEG_LIM_L(limit);
}


void _init_gdt() {
    
    // null
    _set_gdt_entry(0, 0, 0, 0);

    // Ring 0 : Kernel
    _set_gdt_entry(1, 0, 0xfffff, SEG_R0_CODE);
    _set_gdt_entry(2, 0, 0xfffff, SEG_R0_DATA);

    // Ring 3 : User
    _set_gdt_entry(3, 0, 0xfffff, SEG_R3_CODE);
    _set_gdt_entry(4, 0, 0xfffff, SEG_R3_DATA);

}
