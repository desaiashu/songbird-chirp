#ifndef INTERFACE_CONSOLE
#define INTERFACE_CONSOLE

#if ARDUINO
#include <Arduino.h>

template <class type>
void print_to_console(type value) {
    Serial.print(value);  
    Serial.print(" ");   
}

template <class type>
void println_to_console(type value) {
    Serial.println(value);     
}

#else // Mac OSX
#include <iostream>

template <class type>
void print_to_console(type value) {
    std::cout << value; 
    std::cout << " ";    
}

template <class type>
void println_to_console(type value) {
    std::cout << value << std::endl;     
}

#endif

#endif // INTERFACE_CONSOLE
