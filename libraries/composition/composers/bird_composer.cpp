#include "bird_composer.h"

#ifndef ARDUINO
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

#include "../../interface/console.h"
#include "../../sequencing/utils/bird.h"

BirdComposer::BirdComposer() : Composer()
{
    println_to_console("composer created");
    last_opened = 0;
    begin_loop();
}

void copy_file()
{
    println_to_console("copying");
    std::ifstream src("files/live.bird", std::ios::binary);
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
    stat("files/live.bird", &fileInfo);
    time_t last_updated = fileInfo.st_mtime;
    return last_updated;
}

void BirdComposer::file_loop() 
{
    last_opened = 0;
    while (true) { 
        time_t last_updated = updated_time();
        if (last_opened < last_updated)
            read(last_updated);
        
        usleep(500000);
    }
}

void BirdComposer::begin_loop()
{
    file_thread = std::thread(&BirdComposer::file_loop, this);
    file_thread.detach();
}

void BirdComposer::read(time_t last_updated)
{
    copy_file();

    std::ifstream file;
    file.open("files/live.temp");

    if ( file.is_open() ) {
        println_to_console("reading");

        midiclock->clear_update_sequencers(); // clear any pending update as file has changed

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

        midiclock->set_cycle_update(bars); // trigger cycle update to run
    }
    else {
        println_to_console("failed to read");
    }
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline vector<string> get_vector_from_string(std::string s) {
    std::vector<std::string>   result;
    std::stringstream  data(s);
    std::string line;
    while(std::getline(data,line,' '))
    {
        result.push_back(line); // Note: You may get a couple of blank lines
                                // When multiple underscores are beside each other.
    }
    return result;
}

void BirdComposer::process_chunk(vector<string> chunk)
{
    vector<vector<string>> sequence;

    bool data;

    for (string s : chunk) {
        ltrim(s);
        vector<string> line = get_vector_from_string(s);

        if (line[0] == "#") {
            println_to_console("COMMENT");
            data = true;
        } else if (line[0] == "b") {
            data = true;
            bars = stoi(line[1]);
            println_to_console("BARS");
            println_to_console(bars);
        } else {
            sequence.push_back(line);
        }
    }

    if (!data) {
        //sequencers.push_back(construct_sequencer(sequence));
        construct_sequencers(sequence);
        // sequencers.insert(sequencers.end(), seqs.begin(), seqs.end());

    }
        
}

void BirdComposer::construct_sequencers(vector<vector<string>> sequence)
{
    Sequencer* s = new Sequencer(1);

    midiclock->register_update_sequencer(s);

    println_to_console("CONSTRUCTING SEQUENCER");
    // // return sequencers;
}

// void BirdComposer::update_sequencers()
// {
//     midiclock->set_cycle_length(bars);
//     midiclock->update_sequencers(bars, sequencers);
//     // sequencers.clear();
// }

#endif
