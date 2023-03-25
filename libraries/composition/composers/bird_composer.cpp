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
    println_to_console("bird composer");
    last_opened = 0;

    last_note = 0;
    last_velocity = 0;
    last_dur = 0;
    bars = 4; //In case length of bars is not set

    begin_loop();
}

void copy_file()
{
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
        println_to_console("--------------");
        println_to_console("reading");

        // clear any pending update as file has changed
        midiclock->clear_update_sequencers(); 

        // Read and process file, raising a read_exception when it occurs
        read_exception = false;
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

        // Only update the cycle if no read exception occurred
        if (!read_exception) {
            midiclock->set_cycle_update(bars); // trigger cycle update to run
        } else {
            println_to_console("read exception");
            println_to_console("--------------");
            midiclock->clear_update_sequencers(); // clear pending update and wait for next save
        }
        
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

    for (string s : chunk) {
        ltrim(s);
        vector<string> line = get_vector_from_string(s);

        if (line.size() == 0 || line[0] == "#") {
            // ignore empty lines and comments
        } else if (line[0] == "b") {
            try
            {
                bars = stoi(line[1]);
                println_to_console(std::to_string(bars) + " bar cycle");
            }
            catch (...)
            {
                println_to_console("syntax error in # bars, setting to 4");
                bars = 4;
            }
        } else { // ignore empty lines and comments
            sequence.push_back(line);
        }
    }

    if (sequence.size() > 0) {
        construct_sequencers(sequence);
    }
}

void BirdComposer::construct_sequencers(vector<vector<string>> sequence)
{
    //TODO: graceful failure for syntax issues
    Sequencer* s = new Sequencer();

    //velocity vector, since it needs to be preserved
    vector<int> velocity;
    
    for (vector<string> line : sequence) {
        try
        {
            if (line[0] == "ch") {
                int channel = stoi(line[1])-1;
                if (channel < 0 || channel > 15)
                    throw 3;
                s->set_channel(channel);
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
                vector<int> notes = construct_notes(line);
                if (!read_exception)
                    s->gen_notes_sequence(notes, velocity);
            }
        }
        catch (...) // Raise read exception if anything fails
        {
            read_exception = true;
            println_to_console("!! syntax error on following line");
            for (string s : line)
                print_to_console(s+" ");
            println_to_console("--");
        }
    }

    if (!read_exception) {
        midiclock->register_update_sequencer(s);
    }
}

vector<int> BirdComposer::construct_pattern(vector<string> data)
{
    vector<int> pattern;
    for(int i = 1; i < data.size(); i++)
    {
        //TODO: test this functionality
        if (data[i] == "_") {
            int rest_length = 0 - abs(last_dur);
            pattern.push_back(rest_length);
        } else {
            last_dur = dur_from_string(data[i]);
            pattern.push_back(last_dur);
        }
    }

    if (pattern.size() == 0)
        throw 16;

    return pattern;
}

vector<int> BirdComposer::construct_velocities(vector<string> data)
{
    vector<int> velocity;
    for(int i = 1; i < data.size(); i++)
    {
        //TODO: test this functionality (incrementing velocities)
        if (data[i] == "-"){
            velocity.push_back(last_velocity);
        } else if (data[i][0] == '+' || data[i][0] == '-') {
            int new_velocity = last_velocity + stoi(data[i]);
            velocity.push_back(new_velocity);
        } else {
            last_velocity = stoi(data[i]);
            velocity.push_back(last_velocity);
        }
    }

    if (velocity.size() == 0)
        throw 22;

    return velocity;
}

vector<int> BirdComposer::construct_notes(vector<string> data)
{
    vector<int> notes;
    for(int i = 1; i < data.size(); i++)
    {
        //TODO: test this functionality (incrementing notes)
        if (data[i] == "-"){
            notes.push_back(last_note);
        } else if (data[i][0] == '+' || data[i][0] == '-') {
            int new_note = last_note + stoi(data[i]);
            notes.push_back(new_note);
        } else {
            last_note = stoi(data[i]);
            notes.push_back(last_note);
        }
    }

    if (notes.size() == 0)
        throw 14;

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
