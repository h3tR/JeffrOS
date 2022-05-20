#ifndef VGA_DRIVER
#define VGA_DRIVER
#include <stdint-gcc.h>

enum VGA_COLOR{
    black=0,
    blue=1,
    green=2,
    teal=3,
    red=4,
    purple=5,
    orange=6,
    grey=7,
    dark_grey=8,
    licht_blue=9,
    lime=10,
    cyan=11,
    pale_red=12,
    pink=13,
    yellow=14,
    white=15,
};

int GenerateAttribute(int bg, int text);
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void setCursor(uint16_t offset);
void setCursor(int col, int row);
void printChar(char character, int col,int row, char attribute);
void printChar(char character, int col,int row);
void printChar(char character, char attribute);
void printChar(char character, int col,int row);
void printChar(char character);
void printString(const char* string, int col,int row, char attribute);
void printString(const char* string, int col,int row);
void printString(const char* string);
void printString(const char* string, char attribute);
void clearScreen();
void clearRow(int row);
void clearColumn(int col);
void printWarning(const char* string, int col,int row);
void printWarning(const char* string);
void printError(const char* string, int col,int row);
void printError(const char* string);


#endif