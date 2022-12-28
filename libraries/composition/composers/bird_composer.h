#ifndef COMPOSITION_BIRD_COMPOSER
#define COMPOSITION_BIRD_COMPOSER

#ifndef ARDUINO
#include "../composer.h"
#include <ctime>
#include <thread>

class BirdComposer : public Composer {
    private:
        void file_loop();
        void begin_loop();
        void read(time_t last_updated);
        void process_chunk(vector<string> chunk);

        void construct_sequencers(vector<vector<string>> sequence);
        vector<int> construct_pattern(vector<string> data);
        vector<int> construct_notes(vector<string> data);
        vector<int> construct_velocities(vector<string> data);
        Swing construct_swing(vector<string> data);
        Modulator construct_modulator(vector<string> data);
        
        std::thread file_thread;
        time_t last_opened;
        bool read_exception;

        int bars;
        int last_note;
        int last_velocity;
        int last_dur;

    public:
        BirdComposer();

};
#endif

#endif // COMPOSITION_FILE_COMPOSER