#include "../drivers/VGA.h"
#include <stdint-gcc.h>
#include "math.h"
#include "../kernel/Heap.h"
#include "string.h"


//returns the length of given string
int length(const char* string){
    //note that 0x00 doesn't add to the length
    int size=0;
    while (string[size]!=0x00) size++;
    return size;
}

//concatenates a string and a character
const char* concat(const char* s1,char character){
    int l1=length(s1);
    char* str = (char*)malloc(l1+2);
    for(int i=0;i<l1;i++){
        str[i] = s1[i];
        i++;
    }
    str[l1] = character;
    str[l1+1] = 0x00;
    s1 = str;
    return s1;
}

//concatenates two strings
const char* concat(const char* s1,const char* s2){
    int l1 = length(s1); int l2=length(s2);
    char* str = (char*)malloc(l1+l2+1);
    for(int i=0;i<l1;i++){
        str[i]=s1[i];
    }
    for(int i=0;i<l2;i++){
        str[l1+i]=s2[i];
    }
    str[l1+l2]=0x00;
    return str;
}


//turns string to uppercase
const char* uppercase(const char* string){
    int i=0;
    char charArray[length(string)+1];

    while (string[i]!=0x00)
    {
        charArray[i] = string[i];
        if(string[i] >= 0x61 && string[i] <= 0x61+0x1a){
            charArray[i] -= 0x20;
        }
        i++;
    } 
    charArray[i]=0x00;
    string = charArray;
    return string;
}

//turns string to lowercase
const char* lowercase(const char* string){
    int i=0;
    char charArray[length(string)+1];

    while (string[i]!=0x00)
    {
        charArray[i] = string[i];
        if(string[i] >= 0x41 && string[i] <= 0x41+0x1a){
            charArray[i] += 0x20;
        }
        i++;
    }
    charArray[i]=0x00;
    string = charArray;
    return string;
}

//turns given value into a string at given base
const char* tostring(int value, int base){
    if(value==0){
        return "0";
    }
    const char numbers[] = "0123456789abcdef";
    int nrlen = 0;
    int valcopy = value;
    while(valcopy!=0){
        valcopy -=valcopy%base;
        valcopy /= base;
        nrlen++;
    }
    valcopy = value;
    char* string=(char*)malloc((uint32_t)nrlen+1);
    int j=0;
    for(int i = 0;i<nrlen;i++){
        int worknr = valcopy;
        for(int j = 0;j<nrlen-1-i;j++){
            worknr -=worknr%base;
            worknr /= base;
        }
        string[j]=numbers[worknr];
        valcopy-=worknr*pow(base,nrlen-1-i);
        j++;

    }
    string[nrlen]=0x00;
    return string;
}


//returns a string of given hexadecimal number with "0x" prefix
const char* hextostring(int value){
    const char* orig = tostring(value, 16);
    const char* string = concat("0x",orig);
    FreeString(orig);
    return string;
}

const char* tostring(int value){
    return tostring(value, def);
}

//Helper function for freeing a String from the stack
void FreeString(const char* str){
    FreeMemory((void*)str,(uint32_t)length(str)+1);
}

//Similar to Lua's string.split()
//returns a pointer to the output array

//TODO
/*
const char * * split(const char* string, char splitter){
    int splittedcounter=0;
    int i =0;
    while (string[i]!=0x00)
    {
       if(string[i]==splitter) splittedcounter++;
    }
    if(splittedcounter==0){
        const char* array[1] = sizeof()
        return  array;
    }
    const char* * array[splittedcounter];
    i=0;
    int cpyfrom;
    while (string[i]!=0x00)
    {
       if(string[i]==splitter){

       }
    }
    
}
*/