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
const char* tostring(int value, int base);
const char* hextostring(int value);
const char* tostring(int value);
void split(const char* string, char splitter);
void FreeString(const char* str);


#endif