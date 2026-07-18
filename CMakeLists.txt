cmake_minimum_required(VERSION 3.31)
project(MidiSynth)

set(CMAKE_CXX_STANDARD 20)

add_executable(MidiSynth main.cpp
        Synth.cpp
        Synth.h
        utils.h
        utils.cpp
        TrackEvent.cpp
        TrackEvent.h
        MetaEvent.cpp
        MetaEvent.h
        MidiEvent.cpp
        MidiEvent.h
        MidiTrack.cpp
        MidiTrack.h
        MidiSong.cpp
        MidiSong.h
)

add_custom_command(
        TARGET MidiSynth POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Midi Files"
            "${CMAKE_CURRENT_BINARY_DIR}/Midi Files"
        COMMENT "Copying Midi Files directory to build directory..."
)