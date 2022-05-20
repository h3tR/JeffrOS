#include "../drivers/VGA.h"
#include "interrupts/IDT.h"
#include "interrupts/ISR.h"
#include "../libraries/string.h"
#include "../libraries/math.h"
#include "Heap.h"

void main(){
  clearScreen();
  idt_init();
  ClearHeap();
  printString("JeffrOS",34,1,GenerateAttribute(black,yellow));
  printString(" V1.0");
}

