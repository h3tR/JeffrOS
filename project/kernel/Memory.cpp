//#include <stdint-gcc.h>
#include <stdint.h>
#define MEMORY_START 0x10000

int freeMemory=MEMORY_START;

void ClearMemory(){
    freeMemory=MEMORY_START;
}

void* FillMemory(void* dest,uint8_t val,uint32_t size){
    //size = bytes allocated
    unsigned char* destC = (unsigned char*)dest;
    for(int i=0;i<size;i++){
        destC[i] = val;
    }
    return dest;
}

void CopyMemory(unsigned char* src, unsigned char* dest, uint32_t size){
    for(int i=0;i<size;i++){
        src[i] = dest[i];
    }
}

void FreeMemory(unsigned char* src, uint32_t size){
    unsigned char* NextAllocated = src+size;
    CopyMemory(NextAllocated,src,freeMemory-*NextAllocated);
    freeMemory-=size;
}

//a combination of conventional malloc and calloc; already initializes the memory when it gets allocated.
void* malloc(uint32_t size){
    FillMemory((void*)freeMemory, 0, size); 
    void* address = (void*)freeMemory;
    freeMemory += size;
    return address;
}
