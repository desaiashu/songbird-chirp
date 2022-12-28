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
        void process_chunk(vector<string> chunk);
        void update_sequencers();
        void construct_sequencers(vector<vector<string>> sequence);
        void read(time_t last_updated);
        
        std::thread file_thread;
        time_t last_opened;

        int bars;
    public:
        BirdComposer();

};
#endif

#endif // COMPOSITION_FILE_COMPOSER