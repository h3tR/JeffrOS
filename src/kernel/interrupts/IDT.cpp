#include "IDT.h"
#include <stdint-gcc.h>

idt_entry_t idt[IDT_MAX_DESCRIPTORS];

static bool vectors[IDT_MAX_DESCRIPTORS];

__attribute__((aligned(0x10))) 



void IDT_SetDescriptor(uint8_t vector, uint16_t isr, uint8_t flags, uint8_t sel) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = sel; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void IDT_SetDescriptor(uint8_t vector, uint16_t isr, uint8_t flags) {
    IDT_SetDescriptor(vector,isr,flags,0x08);
}

void IDT_SetDescriptor(uint8_t vector, void* isr, uint8_t flags, uint8_t sel) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = sel; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void IDT_SetDescriptor(uint8_t vector, void* isr, uint8_t flags) {
    IDT_SetDescriptor(vector,isr,flags,0x08);
}


extern void* isr_stub_table[];

void IDT_EnableGate(int interrupt){
    idt[interrupt].attributes |= IDT_DESCRIPTOR_PRESENT;
}

void  IDT_Init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < IDT_CPU_EXCEPTION_COUNT; vector++) {
        IDT_SetDescriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti");
    return;
}