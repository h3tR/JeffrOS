#ifndef MEMORY_H
#define MEMORY_H
#include <stdint-gcc.h>

void ClearHeap();
uint32_t getFreeMemory();
void* FillMemory(void* dest,uint8_t val,uint32_t size);
void CopyMemory(void* src, void* dest, uint32_t size);
void FreeMemory(void* src, uint32_t size);
void* malloc(uint32_t size);
void* calloc(uint32_t blocks,uint32_t blockSize);

#endif

