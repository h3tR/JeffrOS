#ifndef STRINGLIB
#define STRINGLIB

enum base{
    bin=2,
    def=10,
    hex=16
};

int length(const char* string);
const char* concat(const char* s1,char character);
const char* concat(const char* s1,const char* s2);
const char* uppercase(const char* string);
const char* lowercase(const char* string);
const char* tostring(int value, int base=10);
const char* hextostring(int value);
void FreeString(const char* str);
//TODO const char * *  split(const char* string, char splitter);


#endif