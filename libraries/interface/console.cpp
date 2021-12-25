#include "console.h"

#if ARDUINO
#include <Arduino.h>

template <class type>
void print_to_console(type value) {
    Serial.println(value);     
}

#else // Mac OSX
#include <iostream>
#include <string>

template <class type>
void print_to_console(type value) {
    std::cout << value << std::endl;     
}

#endif