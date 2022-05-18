#include "../drivers/VGA.h"
#include "interrupts/IDT.h"
#include "interrupts/ISR.h"
#include "../libraries/string.h"
#include "../libraries/math.h"


void main(){
  clearScreen();
  idt_init();
  printString("JeffrOS",34,1,0x0e);
  printString(" V1.0",0x0f);
}

