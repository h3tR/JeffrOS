#include "interrupts/IDT.h"
#include "interrupts/ISR.h"
#include "interrupts/IRQ.h"
#include "Heap.h"
#include <stdint-gcc.h>

//libraries
#include "../libraries/string.h"
#include "../libraries/math.h"

//drivers
#include "../drivers/VGA.h"
#include "../drivers/Keyboard.h"

void main(){
  IDT_Init();
  ISR_Init();
  IRQ_Install();
  ClearHeap();
  clearScreen();
  printString("JeffrOS",34,1,GenerateAttribute(black,yellow));
  printString(" V1.0");
}

