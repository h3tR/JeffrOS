#include <stdint-gcc.h>
#include "../libraries/string.h"
#include "../drivers/VGA.h"
#define HEAP_START 0x10000

uint32_t freeMemory;
void ClearHeap(){
    freeMemory=(uint32_t)HEAP_START;
}

uint32_t getFreeMemory(){
    return freeMemory;
}

void* FillMemory(void* dest,uint8_t val,uint32_t size){
    //size = bytes allocated
    uint8_t* destC = (uint8_t*)dest;
    for(int i=0;i<size;i++){
        destC[i] = val;
    }
    return dest;
}

//Copies memory 
void CopyMemory(void* src, void* dest, uint32_t size){
    uint8_t* pSrc = (uint8_t*)src;
    uint8_t* pDest = (uint8_t*)dest;
    for(int i=0;i<size;i++){
        pSrc[i] = pDest[i];
    }
}

//frees memory of the given size in bytes at given pointer 
//Pretty inefficient but this is the best I can do for now
void FreeMemory(void* src, uint32_t size){
    uint8_t* pSrc = (uint8_t*)src;
    uint8_t* NextAllocated = (uint8_t*)pSrc+size;
    CopyMemory(NextAllocated,pSrc,freeMemory-*NextAllocated);
    freeMemory-=size;
}

//same as conventional malloc but it already initializes the memory when it gets allocated.
void* malloc(uint32_t size){
    FillMemory((void*)freeMemory, 0, size); 
    void* address = (void*)freeMemory;
    freeMemory += size;
    return address;
}

//conventional calloc
void* calloc(uint32_t blocks,uint32_t blockSize){
    uint32_t size = blocks*blockSize;
    FillMemory((void*)freeMemory, 0, size); 
    void* address = (void*)freeMemory;
    freeMemory += size;
    return address;
}
