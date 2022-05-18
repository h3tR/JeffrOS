#ifndef VGA_DRIVER
#define VGA_DRIVER
#include <stdint-gcc.h>

void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void setCursor(uint16_t offset);
void setCursor(int col, int row);
void printChar(char character, int col,int row, char attribute);
void printChar(char character, int col,int row);
void printString(const char* string, int col,int row, char attribute);
void printString(const char* string, int col,int row);
void printString(const char* string);
void printString(const char* string, char attribute);
void clearScreen();
void clearRow(int row);
void clearColumn(int col);

#endif