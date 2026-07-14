cmake_minimum_required(VERSION 3.31)
project(MidiSynth)

set(CMAKE_CXX_STANDARD 20)

add_executable(MidiSynth main.cpp
        Synth.cpp
        Synth.h
        utils.h
        main.cpp
        utils.cpp
        TrackEvent.cpp
        TrackEvent.h
        MetaEvent.cpp
        MetaEvent.h
)
