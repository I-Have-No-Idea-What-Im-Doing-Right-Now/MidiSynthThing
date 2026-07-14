#include <iostream>
#include "MetaEvent.h"

int main() {
	MetaEvent x(0, MetaEventType::copyrightNotice, std::vector<uint8_t>(5));
	std::cout << x.ToString() << std::endl;
}