#ifndef STRINGLIB
#define STRINGLIB

int length(const char* string);
const char* concat(const char* s1,char character);
const char* concat(const char* s1, const char* s2);
const char* uppercase(const char* string);
const char* lowercase(const char* string);
const char* stostring(int value);
const char* tostring(int value, int base);
const char* hextostring(int value);
const char* bintostring(int value);
const char* tostring(int value);
const char* * split(const char* string, char splitter);

#endif