#include <stdint-gcc.h>
#include "IDT.h"
#include "ISR.h"
#include "../drivers/VGA.h"
#include "../libraries/string.h"



void ISR_Init(){

   for(int i =0;i<256;i++){
      IDT_EnableGate(i);
   }
}

 void ExceptionHandler(Registers* regs){
    //TODO
    return;
 }

extern "C" void ISR_Handler(Registers* regs) {
   //TODO
   if(regs->interrupt<32){
      ExceptionHandler(regs);
   }
}


