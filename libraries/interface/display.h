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
        Display(string l1="Scale: C minor", string l2="Lock: off", string l3="Chords: off" );
        void set_label(int label, const string text);
        void update_display();
};

#endif // INTERFACE_DISPLAY
