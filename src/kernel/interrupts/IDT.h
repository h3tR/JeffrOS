#ifndef IDT
#define IDT
#include <stdint-gcc.h>

#define IDT_MAX_DESCRIPTORS 			256
#define IDT_CPU_EXCEPTION_COUNT			32

#define IDT_DESCRIPTOR_X16_INTERRUPT	0x06
#define IDT_DESCRIPTOR_X16_TRAP 		0x07
#define IDT_DESCRIPTOR_X32_TASK 		0x05
#define IDT_DESCRIPTOR_X32_INTERRUPT  	0x0E
#define IDT_DESCRIPTOR_X32_TRAP			0x0F
#define IDT_DESCRIPTOR_RING1  			0x40
#define IDT_DESCRIPTOR_RING2  			0x20
#define IDT_DESCRIPTOR_RING3  			0x60
#define IDT_DESCRIPTOR_PRESENT			0x80

#define IDT_DESCRIPTOR_EXCEPTION		(IDT_DESCRIPTOR_X32_INTERRUPT | IDT_DESCRIPTOR_PRESENT)
#define IDT_DESCRIPTOR_EXTERNAL			(IDT_DESCRIPTOR_X32_INTERRUPT | IDT_DESCRIPTOR_PRESENT)
#define IDT_DESCRIPTOR_CALL				(IDT_DESCRIPTOR_X32_INTERRUPT | IDT_DESCRIPTOR_PRESENT | IDT_DESCRIPTOR_RING3)

typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;
void IDT_SetDescriptor(uint8_t vector, uint16_t isr, uint8_t flags);
void IDT_SetDescriptor(uint8_t vector, uint16_t isr, uint8_t flags, uint8_t sel);
void IDT_SetDescriptor(uint8_t vector, void* isr, uint8_t flags);
void IDT_SetDescriptor(uint8_t vector, void* isr, uint8_t flags, uint8_t sel);
void IDT_EnableGate(int interrupt);
void IDT_Init();

#endif