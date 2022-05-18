#include <stdint-gcc.h>
#include "IDT.h"
#include "../../drivers/VGA.h"
//__attribute__((noreturn))
extern "C" void exception_handler() {
    printString("Interrupt",-1,-1);
    //__asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

 
