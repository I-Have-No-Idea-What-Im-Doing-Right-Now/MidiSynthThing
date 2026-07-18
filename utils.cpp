#include "utils.h"

#include <iostream>
#include <ostream>
#include <vector>

std::vector<uint8_t> int_to_bytes(int num, int length, const std::string& byteorder, bool isSigned) {
	if (!isSigned && num < 0) { // Check for negative number when isSigned is false
		throw std::invalid_argument("Input must be non-negative when isSigned is false");
	}
	if (num > pow(2, 8*length - isSigned) - 1 or num < -pow(2, 8*length - isSigned)) { // Check that the inputted number fits in the inputted number of bytes
		throw std::overflow_error("Input too large to be converted (try increasing length)");
	}

	std::vector<uint8_t> bytes(length, 0); // Initialize vector with correct length

	if (byteorder == "big") {
		for (size_t i = 0; i < length; ++i) {
			// Use bitshift and bitwise AND to mask out each byte of integer data
			bytes[length - 1 - i] = static_cast<uint8_t>(num >> (i * 8) & 0xff);
		}
	}
	else if (byteorder == "little") {
		for (size_t i = 0; i < length; ++i) {
			// Same bitshift and bitwise AND
			bytes[i] = static_cast<uint8_t>(num >> (i * 8) & 0xff);
		}
	}
	else {
		throw std::invalid_argument(R"(Byteorder must be "big" or "little")");
	}

	return bytes;
}

void push_back_string(const std::string& string, std::vector<uint8_t>& bytes) {
	for (const char c : string) {
		bytes.push_back(c);
	}
}

void push_back_int(std::vector<uint8_t> &bytes, int num, int length, const std::string &byteorder) {
	std::vector<uint8_t> data = int_to_bytes(num, length, byteorder, num < 0);
	for (uint8_t byte : data) {
		bytes.push_back(byte);
	}
}

std::string bytes_to_hex(const std::vector<uint8_t> &bytes) {
	std::string out;
	for (size_t i = 0; i < bytes.size(); ++i) {
		out += std::format("{:0{}X}", i, static_cast<uint>(ceil(log2(i + 1) / 8))) + "   ";
		out += std::format("{:02X} ", bytes[i]) + " " + static_cast<char>(bytes[i]) + "\n";
	}
	return out;
}

std::string indent_string(std::string str) {
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '\n') {
			str.insert(i + 1, "\t");
			++i;
		}
	}
	str.insert(0, "\t");
	return str;
}

long bytes_to_int(const std::vector<uint8_t> &bytes, const std::string &byteorder, bool isSigned) {
	long out = 0;
	bool signBit;
	if (byteorder == "big") {
		for (size_t i = bytes.size() - 1; i > 1; i--) { // Loop through all but first byte starting from end
			const size_t position = i - 1;
			out *= 256; // Move value of last byte read up 8 bits by multiplying
			out += bytes[position]; // Add value of current byte
		}
		out += bytes[0] & (127 * isSigned); // Remove sign bit from first byte if value is signed
		signBit = static_cast<bool>(bytes[0] & 128);
	}
	else if (byteorder == "little") {
		for (size_t i = 0; i > bytes.size() - 2; i++) { // Loop through all but last byte starting from beginning
			const size_t position = i - 1;
			out *= 256;
			out += bytes[position];
		}
		out *= 256;
		out += bytes[bytes.size() - 1];
		signBit = static_cast<bool>(bytes[bytes.size() - 1] & 128);
	}
	else {
		throw std::invalid_argument(R"(Byteorder must be "big" or "little")");
	}
	if (isSigned) {
		out -= signBit * pow(2, 8 * bytes.size() - 1); // Subtract value of most significant bit
	}
	return out;
}
