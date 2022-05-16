#ifndef VGA_DRIVER
#define VGA_DRIVER
#include "../utility/typedefs.h"

void setDebugChar(uint8_t c);
void setCursor(uint16_t offset);
void setCursor(int col, int row);
void printChar(char character, int col,int row, char attribute);
void printChar(char character, int col,int row);
void printString(const char* string, int col,int row, char attribute);
void printString(const char* string, int col,int row);
void clearScreen();
void clearRow(int row);
void clearColumn(int col);

#endif