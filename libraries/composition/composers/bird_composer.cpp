#include "bird_composer.h"

#ifndef ARDUINO
#include <iostream>
#include <fstream>
#include <string>
using std::string;
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

#include "../../interface/console.h"

BirdComposer::BirdComposer() : Composer()
{
    println_to_console("composer created");
    last_opened = 0;

    last_note = 0;
    last_velocity = 0;
    last_dur = 0;

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
            while (file && line != "") { // this while loop groups things into chunks, separated by a newline
                chunk.push_back(line);
                std::getline(file, line);
            }
            process_chunk(chunk); //decoding work happens here!
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
    //TODO: graceful failure for syntax issues
    Sequencer* s = new Sequencer();

    //TODO: set these to false and check if valid // gracefully fail
    //If invalid, throw legible error in console and don't update patterns
    bool valid_channel = true;
    bool valid_pattern = true;
    bool valid_velocities = true;
    bool valid_notes = true;

    //velocity vector, since it needs to be preserved
    vector<int> velocity;
    
    for (vector<string> line : sequence) {

        if (line[0] == "ch") {
            s->set_channel(stoi(line[1]));

        } else if (line[0] == "p") {
            s->pattern = construct_pattern(line);

        } else if (line[0] == "sw") {
            s->swing = construct_swing(line);

        } else if (line[0] == "m") {
            s->mod = construct_modulator(line);

        } else if (line[0] == "v") {
            velocity.clear();
            velocity = construct_velocities(line);

        } else if (line[0] == "n") {
            s->gen_notes_sequence(construct_notes(line), velocity);

        }
    }

    if (valid_channel && valid_pattern && valid_velocities && valid_notes) {
        midiclock->register_update_sequencer(s);
        println_to_console("CONSTRUCTING SEQUENCER");
    }

}

vector<int> BirdComposer::construct_pattern(vector<string> data)
{
    vector<int> pattern;
    for(int i = 1; i < data.size(); i++)
    {
        //TODO: test this functionality
        if (data[i][0] == '_') {
            int rest_length = 0 - abs(last_dur);
            pattern.push_back(rest_length);
        } else {
            last_dur = dur_from_string(data[i]);
            pattern.push_back(last_dur);
        }
    }
    return pattern;
}

vector<int> BirdComposer::construct_velocities(vector<string> data)
{
    vector<int> velocity;
    for(int i = 1; i < data.size(); i++)
    {
        //TODO: test this functionality (incrementing velocities)
        if (data[i][0] == '+' || data[i][0] == '-') {
            int new_velocity = last_velocity + stoi(data[i]);
            velocity.push_back(new_velocity);
        } else {
            last_velocity = stoi(data[i]);
            velocity.push_back(last_velocity);
        }
    }
    return velocity;
}

vector<int> BirdComposer::construct_notes(vector<string> data)
{
    vector<int> notes;
    for(int i = 1; i < data.size(); i++)
    {
        //TODO: test this functionality (incrementing notes)
        if (data[i][0] == '+' || data[i][0] == '-') {
            int new_note = last_note + stoi(data[i]);
            notes.push_back(new_note);
        } else {
            last_note = stoi(data[i]);
            notes.push_back(last_note);
        }
    }
    return notes;
}

Swing BirdComposer::construct_swing(vector<string> data)
{
    int swing_amount = 1;
    int base = x;
    bool humanize = false;
    //TODO: read swing
    return Swing();
}

Modulator BirdComposer::construct_modulator(vector<string> data)
{
    mod_type type=NO_MOD;
    int cycle_length=0;
    double max_mod=0.2;
    bool step_based=false;
    //TODO: read modulator
    return Modulator();
}



#endif
