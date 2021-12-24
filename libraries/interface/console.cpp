#include "console.h"

#if ARDUINO
#include <Arduino.h>
void print_to_console(const char* str) {
    Serial.println(str);     
}

#else
#include <iostream>

void print_to_console(const char* str) {
    std::cout << str << std::endl;     
}

#endif