#ifndef UTILS_H
#define UTILS_H

#include "type_traits"
#include <vector>

template<typename T>
requires std::is_arithmetic_v<T> // Using a template so that the function can take any number type
int sign(T x) {
	if (x > T(0)) return 1;
	if (x < T(0)) return -1;
	return 0;
}

std::vector<uint8_t> int_to_bytes(int num, int length, const std::string& byteorder, bool isSigned);
void push_back_string(const std::string& string, std::vector<uint8_t>& bytes);
void push_back_int(std::vector<uint8_t>& bytes, int num, int length, const std::string& byteorder);
std::string bytes_to_hex(const std::vector<uint8_t>& bytes);
std::string indent_string(std::string str);
long bytes_to_int(const std::vector<uint8_t>& bytes, const std::string& byteorder, bool isSigned = false);

#endif //UTILS_H
