#ifndef SYNTH_H
#define SYNTH_H

#include <iostream>
#include <ostream>
#include <vector>
#include <type_traits>
#include "utils.h"

class Synth {
public:
    Synth(int channels = 1, int samplerate = 44100, int bitsPerSample = 16);
    virtual ~Synth() = default;

    void GenerateFile(double length, double volume = 0.8, double frequency = 440, const std::string& filename = "file.wav", bool printData = false) {
        DoGenerateFile(length, volume, frequency, filename, printData);
    }
protected:
    [[nodiscard]] double GetSampleTime(int sampleNum) const;

    [[nodiscard]] double MakeSineData(int sampleNum, double frequency) const;

    [[nodiscard]] double MakeSquareData(int sampleNum, double frequency) const;

    [[nodiscard]] double MakeTriangleData(int sampleNum, double frequency) const;

    [[nodiscard]] double MakeSawtoothData(int sampleNum, double frequency) const;

    [[nodiscard]] double MakeSampleData(int sampleNum, double frequency) const;

    template <typename T>
    requires std::is_floating_point_v<T>
    [[nodiscard]] std::vector<uint8_t> FloatToSampleData(T value) const {
        //std::cout << value << std::endl;
        // Value parameter will be between -1 and 1
        const bool isSigned = bitsPerSample > 8; // Bit depths over 8 use 2's compliment
        double n = value;
        if (!isSigned) {
            n += 1.0;
            n *= 0.5;
        }
        n *= pow(2, bitsPerSample-isSigned) - 1; // Kinda forgot how this math works
        const int intValue = static_cast<int>(n); // Convert to integer
        return int_to_bytes(intValue, bitsPerSample / 8, "little", isSigned);

    }

    virtual std::vector<uint8_t> GenerateSoundData(double length, double volume, double frequency);

private:
    int channels;
    int samplerate;
    int bitsPerSample;

    // Private virtual DoGenerateFile to safely use default arguments for generate file
    virtual void DoGenerateFile(double length, double volume, double frequency, const std::string& filename, bool printData);
};

#endif //SYNTH_H
