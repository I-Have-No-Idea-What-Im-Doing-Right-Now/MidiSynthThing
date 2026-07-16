#include "MidiSong.h"
#include <iostream>
#include <fstream>

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
	if 
}

std::string MidiSong::ToString() const {
}
