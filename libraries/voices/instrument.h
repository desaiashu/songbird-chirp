#ifndef VOICES_INSTRUMENT
#define VOICES_INSTRUMENT

class Instrument {
    private:
        int midi_channel;

    public:
        Instrument(int midi_channel=0);
        void start_note(int note, int velocity);
        void end_note(int note, int velocity);
};

#endif // VOICES_INSTRUMENT