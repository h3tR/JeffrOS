#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Default scheme attribute byte (white on black)
#define DEFAULT_ATTRIBUTE 0x0f

// I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#include "../utility/typedefs.h"
#include "../drivers/portIO.h"

void setDebugChar(uint8_t c){
    uint8_t *vidmem = (uint8_t*) 0xb8000;
    *vidmem = c;
}

uint16_t cursor = 0;

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

void setCursor(int col, int row) {
    setCursor(col+row*MAX_COLS);
    return;
}

void printChar(char character, int col,int row, char attribute){
    //video memory pointer
    uint8_t *vidmem = (uint8_t*) VIDEO_ADDRESS;
    uint16_t offset = cursor;
    if(col>=0&&row>=0){
       setCursor(col,row);
       offset = cursor;
    }
    if(character ==  '\n'){
        setCursor(79,offset/(2*MAX_COLS));
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

void printChar(char character, int col,int row){
    printChar(character,col,row,DEFAULT_ATTRIBUTE);
}

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

void printString(const char* string, int col,int row){
    printString(string,col,row,DEFAULT_ATTRIBUTE);
    return;
}

void clearRow(int row){
    int col = 0;

    for(col;col<MAX_COLS;col++){
        printChar(' ',col,row);
    }
}

void clearColumn(int col){
    int row = 0;

    for(row;row<MAX_ROWS;row++){
        printChar(' ',col,row);
    }
}

void clearScreen(){
    int row = 0;
    for(row;row<MAX_ROWS;row++){
        clearRow(row);
    }
}
