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
        
        usleep(500000);
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

    if ( file.is_open() ) {
        println_to_console("reading");

        midiclock->purge_sequencers();

        while ( file ) { // equivalent to myfile.good()
            vector<string> chunk;
            std::string line;
            std::getline(file, line);
            while (file && line != "") {
                chunk.push_back(line);
                std::getline(file, line);
            }
            process_chunk(chunk);
        }
        file.close();
        destroy_file();
        last_opened = last_updated;
    }
    else {
        println_to_console("failed to read");
    }
}

void LiveComposer::update_sequencers(std::ifstream file)
{

    

    

    // BassSequencer* bass = new BassSequencer(progression, 8*dur::w, 1);
    // sequencers. push_back(bass);

    // // GrooveSequencer* drums = new GrooveSequencer(4*dur::w, 1);
    // // sequencers.push_back(drums);

    // midiclock->register_sequencer(chords);
    // midiclock->register_sequencer(bass);
    // midiclock->register_sequencer(harmony);
}

void LiveComposer::process_chunk(vector<string> chunk)
{
    
    println_to_console("chunk ");
    for (string s : chunk) {
        println_to_console(s);
    }
    println_to_console("----");
}

#endif
