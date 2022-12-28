# Bird notation 

Bird is a musical notation designed for composition of modern electronic music. You can think of it like Markdown for music.

The notation builds on top of ideas from sheet music and MIDI and is optimized for the following:
- Fast to write using a qwerty keyboard
- Fast composition of multiple song sections
- Enables automation of melodic ideas, synthesis parameters, and FX through an arrangement
- Enables use (and re-use) of mathematical ideas in composition
- Enables use (and re-use) of common musical patterns in composition

These optimizations come with some shortcomings:
- Less human readable than sheet music or MIDI editors
- Fewer features, and less time precise than modern MIDI editors
- Slower to write than recording MIDI from a keyboard

The notation is best suited for any of the following:
- Musicians who are not proficient at writing sheet music or programming/recording MIDI in a DAW
- Electronic musicians seeking to speed up their composition
- Musicians from a math / computer science background

The Songbird software platform reads bird files and interacts with a DAW through a virtual MIDI port, similar to a software or hardware sequencer. In the future, the notation will be visualizable/exportable as sheet music and MIDI/piano roll.

Most commonly, the bird notation will be used in tandem with audio recording techniques and DAW manupulation rather than as a standalone composition tool. Think of bird as the "computer based" composition tool, while audio recording of instrumentalists/vocalists in DAWs will provide an oft necessary "human" element to the compositions.

## Current state and use cases

At present, the bird notation and songbird platform support single-section loop based composition. This enables for rapid ideation and iteration, similar to live-coding.

Eventually, the notation and platform will support longer form composition through arrangement, including song sections, creating tension through FX, changing tempo, and more.

## Syntax and example

### Syntax

```
ch - midi channel
p - pattern (w:1/1 q:1/4 x:1/16, _:rest of same length, _q:1/4 rest)
sw - swing (-:straight <:drag >:rush, #:amount, x:1/16 , ~:humanize)
m - modulation (sin:sinewave, tri:triangle, #:percent)
v - velocity to loop
n - notes to loop (#:midinote, -:repeat, +1:add to root, -2:subtract from root)
cc - midi control change
sec - section 
arr - arrangement (intro:name #:length in bars)
```

### Example

```
arr
  verse 8
  chorus 8
  verse 8
  chorus 8

sec verse

  ch 0 chords
    p w _ w _
      sw - ~
        v 70 90 100
          n 60 - -
          n +3 +5 +4
        v 60
          n +7 +7 +8
        v 30
          n +12
```

## Roadmap

### Near term
- Better documentation on installing // running locally
- Euclidean rythyms
- Pre-saved patterns (pt)
- Better humanize algo based on scientific research
- Inputting notes with names
- Inputting chords with words
- Different update cycle lengths of diff sequencers
- Syntax highlighting for .bird files
- Arrangement implementation
- Get song position info from MIDI to establish ticks

### Bugs
- 3 chord loop repeats the first (or perhaps bc it's repeating on 8)

### Long term ideas
- Standalone songbird executable that reads / runs
- More human readable visualization
- Visualization in MIDI / sheet music
- More features to enable complex compositions
