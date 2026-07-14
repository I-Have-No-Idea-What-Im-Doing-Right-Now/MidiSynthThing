#include <iostream>

#include "TrackEvent.h"
#include "MetaEvent.h"
#include "MidiEvent.h"

int main() {
	TrackEvents::MidiEvent x(0, TrackEvents::MidiEventType::noteOn, 0, std::vector<uint8_t>(5));
	std::cout << x.ToString() << std::endl;
}
