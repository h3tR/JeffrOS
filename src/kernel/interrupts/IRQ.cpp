#include "../../drivers/portIO.h"
#include "ISR.h"
#include "IDT.h"
#include <stdint-gcc.h>


extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

uint32_t IRQS[16]={
    (uint32_t)irq0,
    (uint32_t)irq1,
    (uint32_t)irq2,
    (uint32_t)irq3,
    (uint32_t)irq4,
    (uint32_t)irq5,
    (uint32_t)irq6,
    (uint32_t)irq7,
    (uint32_t)irq8,
    (uint32_t)irq9,
    (uint32_t)irq10,
    (uint32_t)irq11,
    (uint32_t)irq12,
    (uint32_t)irq13,
    (uint32_t)irq14,
    (uint32_t)irq15
};

void *IRQ_Routines[16] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};


void IRQ_InstallHander(int irq, void (*handler)(Registers* regs))
{
	IRQ_Routines[irq] = (void*)handler;
}


void IRQ_UninstallHander(int irq)
{
	IRQ_Routines[irq] = 0;
}


void IRQ_Remap(void)
{
	b_out(0x20, 0x11);
	b_out(0xA0, 0x11);
	b_out(0x21, 0x20);
	b_out(0xA1, 0x28);
	b_out(0x21, 0x04);
	b_out(0xA1, 0x02);
	b_out(0x21, 0x01);
	b_out(0xA1, 0x01);
	b_out(0x21, 0x0);
	b_out(0xA1, 0x0);
}


void IRQ_Install()
{
	IRQ_Remap();

    for(int i=0;i<16;i++){
	    IDT_SetDescriptor((uint8_t)32+i, IRQS[i], (uint8_t)0x08, (uint8_t)0x8E);
    }
}

int currentInterrupt = -1;

extern "C" void IRQ_Handler(Registers* regs)
{
	currentInterrupt = regs -> interrupt;
	void (*handler)(Registers* regs);

	
	handler = (void (*)(Registers*))IRQ_Routines[regs->interrupt - 32];
	if (handler)
	{
		handler(regs);
	}


	if (regs->interrupt >= 40)
	{
		b_out(0xA0, 0x20);
	}


	b_out(0x20, 0x20);
}

void irq_wait(int n){
    while(currentInterrupt != n){};
    currentInterrupt = -1;

}