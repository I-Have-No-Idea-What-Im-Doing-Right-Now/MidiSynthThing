//
// Created by Leo Pilcher on 7/16/26.
//

#ifndef MIDISYNTH_MIDISONG_H
#define MIDISYNTH_MIDISONG_H

#include <vector>
#include "MidiTrack.h"

class MidiSong {
	public:
		explicit MidiSong(const std::vector<uint8_t>& midiFile, bool debugPrint = false);
		explicit MidiSong(const std::string& filename, bool debugPrint = false);
		[[nodiscard]] std::string ToString() const;

		std::vector<MidiTrack> tracks;
		uint16_t fileFormat;
		uint16_t numTracks;
		int16_t division;
	private:
		void InitializeFromFileBytes(const std::vector<uint8_t>& midiFile, bool debugPrint);
};


#endif //MIDISYNTH_MIDISONG_H
