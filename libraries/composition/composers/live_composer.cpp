#include "file_composer.h"

#ifndef ARDUINO
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "../../interface/console.h"

LiveComposer::LiveComposer() : Composer()
{
    println_to_console("composer created");
    last_opened = 0;
    begin_loop();
}

void LiveComposer::delete_sequencers()
{
    
}

void copy_file()
{
    std::ifstream src("files/live.txt", std::ios::binary);
    std::ofstream dst("files/live.temp", std::ios::binary);

    dst << src.rdbuf();
}

void destroy_file()
{
    std::remove("files/live.temp");
}

time_t updated_time()
{
    struct stat fileInfo;
    stat("files/live.txt", &fileInfo);
    time_t last_updated = fileInfo.st_mtime;
    return last_updated;
}

void LiveComposer::file_loop() 
{
    while (true) {    
        time_t last_updated = updated_time();
        if (last_opened < last_updated)
            read(last_updated);
        
        usleep(200000);
    }
}

void LiveComposer::begin_loop()
{
    file_thread = std::thread(&LiveComposer::file_loop, this);
    file_thread.detach();
}

void LiveComposer::read(time_t last_updated)
{
    copy_file();

    std::ifstream file;
    file.open("files/live.temp");
    std::string next;

    if ( file.is_open() ) {
        println_to_console("reading");
        while ( file ) { // equivalent to myfile.good()
            std::getline (file, next);
        }
        file.close();
        destroy_file();
        last_opened = last_updated;
    }
    else {
        println_to_console("failed to read");
    }
}

void LiveComposer::update()
{
    
}

#endif
