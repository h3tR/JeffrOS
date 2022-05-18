#include "../drivers/VGA.h"
#include <stdint-gcc.h>
#include "math.h"


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
    char str[l1];
    int i=0;
    for(int j=0;j<l1;j++){
        str[i] = s1[j];
        i++;
    }
    str[l1] = character;
    str[l1+1] = 0x00;
    s1 = str;
    return s1;
}

//concatenates two strings
const char* concat(const char* s1, const char* s2){

   //TODO
    return s1;
}


//turns string to uppercase
const char* uppercase(const char* string){
    int i=0;
    char charArray[length(string)];

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
    char charArray[length(string)];

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

//temporary debug function for single digit number display
const char* stostring(int value){
    const char numbers[] = "0123456789abcdef";
    return concat("",numbers[value]);
}

/*tostring and similar functions do not yet work due 
to dependance on the unfinished concat() function*/
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
    const char* string = "";
    for(int i = 0;i<nrlen;i++){
        int worknr = valcopy;
        for(int j = 0;j<nrlen-1-i;j++){
            worknr -=worknr%base;
            worknr /= base;
        }
        const char* tString = concat(string,numbers[worknr]);
        valcopy-=worknr*pow(base,nrlen-1-i);
        string = tString;
    }
    return string;
}

const char* hextostring(int value){
    return tostring(value, 16);
}

const char* bintostring(int value){
    return tostring(value, 2);
}

const char* tostring(int value){
    return tostring(value, 10);
}

//Similar to Lua's string.split()
//returns a pointer to the output array
void split(const char* string, char splitter){
    //TODO
}
