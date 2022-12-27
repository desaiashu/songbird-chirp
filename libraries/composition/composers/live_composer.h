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
        void update();
        void read(time_t last_updated);
        void delete_sequencers();
        
        std::thread file_thread;
        time_t last_opened;
    public:
        LiveComposer();

};
#endif

#endif // COMPOSITION_FILE_COMPOSER