#ifndef INTERFACE_DISPLAY
#define INTERFACE_DISPLAY

#include <string>

class Display {
    private:
        int test;

    public:
        Display();
        void setLabel1(const std::string& text);
        void setLabel2(const std::string& text);
};

#endif // INTERFACE_DISPLAY
