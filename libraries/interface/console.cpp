#include "console.h"

#if ARDUINO
#include <Arduino.h>
void print_to_console(const char* str) {
    Serial.println(str);     
}

void print_to_console(int i) {
    Serial.println(i);   
}

#else // Mac OSX
#include <iostream>
#include <string>

void print_to_console(const char* str) {
    std::cout << str << std::endl;     
}

void print_to_console(int i) {
    std::cout << i << std::endl;   
}

#endif