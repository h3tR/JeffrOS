#ifndef IRQ
#define IRQ
#include "ISR.h"

void IRQ_InstallHander(int irq, void (*handler)(Registers* regs));
void IRQ_UninstallHander(int irq);
void IRQ_Remap(void);
void IRQ_Install();
void irq_wait(int n);

#endif