#include <iostream>
#include <vector>
#include "MetaEvent.h"
#include "MidiEvent.h"
#include "MidiTrack.h"
#include "utils.h"

int main() {
	std::vector<TrackEvent*> events;
	for (int i = 0; i < 20; i++) {
		MetaEvent e = MetaEvent(0, MetaEventType::copyrightNotice, std::vector<uint8_t>(40));
		events.push_back(&e);
	}
	MidiTrack track(events);
	std::cout << track.ToString() << std::endl;
	std::cout << bytes_to_hex(std::vector<uint8_t>(10));
}
