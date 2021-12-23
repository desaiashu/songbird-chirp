#include <Arduino.h>
#include <string>

class Display {

public:
    Display();
    void setLabel1(const std::string& text);
    void setLabel2(const std::string& text);

    int test;
};



