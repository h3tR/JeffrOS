#define VIDEO_ADDRESS 0xb8000
#define VIDEO_ADDRESS_GRAPHICS 0xa0000

#define MAX_ROWS 25
#define MAX_COLS 80
// Default scheme attribute byte (white on black)
#define DEFAULT_ATTRIBUTE 0x0f

// I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#include <stdint-gcc.h>
#include "../drivers/portIO.h"
#include "VGA.h"
#include "../libraries/string.h"
#include "../kernel/Heap.h"

//TODO supposed to be part of the upcoming VA graphics library
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)VIDEO_ADDRESS_GRAPHICS + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

//Character Attribute helper function
int GenerateAttribute(int bg, int text){
    return bg*16+text;
}

uint16_t cursor = 0;

//sets cursor to memory offset
void setCursor(uint16_t offset){
    if(offset>=0&&offset<2000){
        b_out(REG_SCREEN_CTRL, 0x0f);
        b_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
        b_out(REG_SCREEN_CTRL, 0x0e);
        b_out(REG_SCREEN_DATA, (uint8_t)((offset >> 8) & 0xff));
        cursor = offset;
    }
    return;
}

/*
returns an array containing:
    the current column at index 0 
    the current row at index 1
*/
void getCursor(int dat[2]){
    int RealCursor = cursor;
    int col = RealCursor%MAX_COLS;
    int row = (RealCursor-col)/MAX_COLS;
    dat[0] = col;
    dat[1] = row;
   return;
}

//sets cursor to given position
void setCursor(int col, int row) {
    setCursor(col+row*MAX_COLS);
    return;
}

/*prints out a single character at given position 
    (optional: defaults to cursor)
        and with given VGA attribute 
    (optional: defaults to 0x0f = white text on black background)
 */
void printChar(char character, int col, int row, char attribute){
    //video memory pointer
    uint8_t *vidmem = (uint8_t*) VIDEO_ADDRESS;
    uint16_t offset = cursor;
    if(col>=0&&row>=0){
       setCursor(col,row);
       offset = cursor;
    }
    if(character ==  '\n'){
        int cursorData[2];
        getCursor(cursorData);
        setCursor(0,cursorData[1]+1);
        offset = cursor;
    } else {
       *(vidmem+offset*2) = character;
       *(vidmem+offset*2+1) = attribute;
    }
    offset++;
    //TODO offset = handlescrolling(offset);
    setCursor(offset);
    return;
}
/*prints out a string at given position 
    (optional: defaults to cursor)
        and with given VGA attribute 
    (optional: defaults to 0x0f = white text on black background)
 */
void printString(const char* string, int col,int row, char attribute){
    //Memory location of first character
    uint8_t* pChar = (uint8_t*) string;
    //print character until string termination
    while (*pChar != 0x00)
    {
        printChar(*pChar,col,row,attribute);
        pChar++;
        col++;
        if(col>MAX_COLS){
            col = 0;
            row++;
        }
    }
    return;
}


//clears given row
void clearRow(int row){
    int col = 0;

    for(col;col<MAX_COLS;col++){
        printChar(' ',col,row);
    }
}

//clears given column
void clearColumn(int col){
    int row = 0;

    for(row;row<MAX_ROWS;row++){
        printChar(' ',col,row);
    }
}

//clears the entire screen
void clearScreen(){
    int row = 0;
    for(row;row<MAX_ROWS;row++){
        clearRow(row);
    }
    setCursor(0);
}

void printWarning(const char* string, int col,int row){
    printString(concat("Warning: ",string),col,row,GenerateAttribute(black,yellow));
}

void printError(const char* string, int col,int row){
    printString(concat("Error: ",string),col,row,GenerateAttribute(black,red));
}
