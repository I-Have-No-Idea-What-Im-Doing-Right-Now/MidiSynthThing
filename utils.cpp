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
