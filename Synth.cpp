//
// Created by Leo on 7/10/26.
//

#include "Synth.h"
#include "utils.h"
#include <iostream>
#include <fstream>

Synth::Synth(int channels, int samplerate, int bitsPerSample) {
	this->channels = channels;
	this->samplerate = samplerate;
	this->bitsPerSample = bitsPerSample;
}

double Synth::GetSampleTime(int sampleNum) const {
	return static_cast<double>(sampleNum) / static_cast<double>(samplerate);
}

double Synth::MakeSineData(int sampleNum, double frequency) const {
	return sin(2.0 * M_PI * frequency * GetSampleTime(sampleNum));
}

double Synth::MakeSquareData(int sampleNum, double frequency) const {
	return sign(MakeSineData(sampleNum, frequency));
}

double Synth::MakeTriangleData(int sampleNum, double frequency) const {
	return (2.0 / M_PI) * asin(sin(2.0 * M_PI * frequency * GetSampleTime(sampleNum)));
}

double Synth::MakeSawtoothData(int sampleNum, double frequency) const {
	return 2 * std::fmod(frequency * GetSampleTime(sampleNum), 1) - 1;
}

double Synth::MakeSampleData(int sampleNum, double frequency) const {
	return MakeSineData(sampleNum, frequency);
}

std::vector<uint8_t> Synth::GenerateSoundData(double length, double volume, double frequency) {
	const int datasize = ceil(length * samplerate * channels * bitsPerSample / 8); // Size of sample data in bytes
	const int bytespersample = bitsPerSample / 8;
	std::vector<uint8_t> data;

	for (uint i = 0; i < datasize; i += bytespersample * channels) {
		const uint sampleNum = i / (bytespersample * channels);
		std::cout << sampleNum << std::endl;
		for (ushort channelNumber = 0; channelNumber < channels; channelNumber++) {
			for (std::vector<uint8_t> sampledata = FloatToSampleData(volume * MakeSampleData(sampleNum, frequency)); uint8_t byte : sampledata) {
				data.push_back(byte);
			}
		}
	}
	return data;
}

void Synth::DoGenerateFile(double length, double volume, double frequency, const std::string& filename, bool printData) {
	const int datasubchunksize = ceil(length * samplerate * channels * bitsPerSample / 8);
	std::vector<uint8_t> data;

	push_back_string("RIFF", data); // RIFF header
	push_back_int(data, datasubchunksize + 36, 4, "little");; // Size of file data after this point (filesize - 8)
	push_back_string("WAVE", data); // Wave format

	push_back_string("fmt ", data); // ID for format subchunk
	push_back_int(data, 16, 4, "little"); // Size of the rest of the subchunk in bytes (always 16)
	push_back_int(data, 1, 2, "little"); // Compression. Set to 1 for no compression
	push_back_int(data, channels, 2, "little"); // Number of channels
	push_back_int(data, samplerate, 4, "little"); // Samplerate
	push_back_int(data, channels * samplerate * bitsPerSample / 8, 4, "little"); // Byte rate
	push_back_int(data, channels * bitsPerSample / 8, 2, "little"); // Block align
	push_back_int(data, bitsPerSample, 2, "little"); // Bits per sample

	push_back_string("data", data); // ID for data subchunk
	push_back_int(data, datasubchunksize, 4, "little");

	std::vector<uint8_t> soundData = GenerateSoundData(length, volume, frequency);
	for (uint8_t byte : soundData) {
		data.push_back(byte);
	}
	if (printData) {
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << std::format("{:0{}X}", i, static_cast<uint>(ceil(log2(i + 1) / 8))) << "   ";
			std::cout << std::format("{:02X} ", data[i]) << " " << data[i] << std::endl;
		}
	}

	std::ofstream out(filename);
	out.write(reinterpret_cast<char*>(&data[0]), static_cast<long>(data.size()));
	out.close();
}
