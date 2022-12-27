#ifndef COMPOSITION_LIVE_COMPOSER
#define COMPOSITION_LIVE_COMPOSER

#ifndef ARDUINO
#include "../composer.h"
#include <ctime>
#include <thread>

class LiveComposer : public Composer {
    private:
        void file_loop();
        void begin_loop();
        void update_sequencers(std::ifstream file);
        void process_chunk(vector<string> chunk);
        void read(time_t last_updated);
        
        std::thread file_thread;
        time_t last_opened;
    public:
        LiveComposer();

};
#endif

#endif // COMPOSITION_FILE_COMPOSER