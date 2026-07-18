#include "MidiSong.h"
#include <iostream>
#include <fstream>

#include "utils.h"

MidiSong::MidiSong(const std::vector<uint8_t>& midiFile, bool debugPrint) {
	InitializeFromFileBytes(midiFile, debugPrint);
}

MidiSong::MidiSong(const std::string& filename, bool debugPrint) {
	// Open file in binary mode with read pointer at the end (ate)
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open()) throw std::runtime_error("Failed to open file: " + filename);
	// Get size of file by getting position of read pointer while at the end
	const std::streamsize size = file.tellg();

	file.seekg(0, std::ios::beg); // Move read pointer to start of the file
	std::vector<uint8_t> fileBytes(size); // Initialize vector with correct size

	// Read file into the vector
	if (!file.read(reinterpret_cast<char*>(fileBytes.data()), size)) {
		throw std::runtime_error("Failed to read file: " + filename);
	}
	InitializeFromFileBytes(fileBytes, debugPrint);
}

void MidiSong::InitializeFromFileBytes(const std::vector<uint8_t> &midiFile, bool debugPrint) {
	if (std::string(midiFile.begin(), midiFile.begin() + 4) != "MThd") {
		throw std::invalid_argument("Provided file is not a valid Midi file");
	}

	// Format of Midi file. 0 = single track, 1 = multiple track, 2 = multiple song
	fileFormat = bytes_to_int(std::vector(midiFile.begin() + 8, midiFile.begin() + 10), "big");
	if (fileFormat == 2) throw std::invalid_argument("Multiple song Midi format not supported");

	numTracks = bytes_to_int(std::vector(midiFile.begin() + 10, midiFile.begin() + 12), "big");

	// Number of units per beat
	division = bytes_to_int(std::vector(midiFile.begin() + 12, midiFile.begin() + 14), "big", true);

	if (division <= 0) throw std::invalid_argument("Files with negative division value not supported");

	if (std::string(midiFile.begin() + 14, midiFile.begin() + 18) != "MTrk") {
		throw std::invalid_argument("File is not valid. Failed to read header of first Midi track");
	}

	// Get length of first track in bytes
	uint32_t trackLength = bytes_to_int(std::vector(midiFile.begin() + 18, midiFile.begin() + 22), "big");
	uint position = 22; // Keep track of position, starting at the first byte of track data

	for (uint16_t i = 0; i < numTracks; i++) {
		// Get data of track
		const std::vector trackData(midiFile.begin() + position, midiFile.begin() + position + trackLength);
		MidiTrack track(trackData);
		tracks.push_back(track); // Construct new Midi track on back of tracks using trackData
		position += trackLength + 4; // Move over track data and header for next track
		trackLength = bytes_to_int(std::vector(midiFile.begin() + position, midiFile.begin() + position + 4), "big");
		position += 4;
		if (!debugPrint) continue;
		std::cout << track.ToString() << std::endl;
	}
}

std::string MidiSong::ToString() const {
	std::string out;
	for (const MidiTrack& track : tracks) {
		out.append(track.ToString() + "\n");
	}
	return out;
}
