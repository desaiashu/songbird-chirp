#ifndef INTERFACE_DISPLAY
#define INTERFACE_DISPLAY

#include <string>
using std::string;

class Display {
    private:
        int test;

    public:
        Display();
        void setLabel1(const string text);
        void setLabel2(const string text);
};

#endif // INTERFACE_DISPLAY
