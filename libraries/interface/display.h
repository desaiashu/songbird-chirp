#ifndef INTERFACE_DISPLAY
#define INTERFACE_DISPLAY

#include <string>
using std::string;

class Display {
    private:
        int test;
        string label_1;
        string label_2;
        string label_3;

    public:
        Display(string l1="Scale: C minor", string l2="Scale Lock: off", string l3="Channel: 8");
        void set_label(int label, const string text);
        void update_display();

        static Display& getInstance()
        {
            static Display instance;
            return instance;
        }
};

#ifndef DISPLAY_IO
#define DISPLAY_IO
static Display* d = &Display::getInstance();
#endif // !DISPLAY_IO

#endif // INTERFACE_DISPLAY
