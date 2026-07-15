#include <iostream>
#include <vector>
#include "MetaEvent.h"
#include "MidiEvent.h"
#include "MidiTrack.h"
#include "utils.h"

int main() {
	std::vector<TrackEvent*> events;
	MetaEvent e(20, MetaEventType::copyrightNotice, std::vector<uint8_t>(1));
	for (int i = 0; i < 20; i++) {
		e = MetaEvent(20, MetaEventType::copyrightNotice, std::vector<uint8_t>(3));
		events.push_back(&e);
	}
	MidiTrack track(events);
	std::cout << track.ToString() << std::endl;

	MetaEvent m = MetaEvent(20, MetaEventType::copyrightNotice, std::vector<uint8_t>(3));
	std::cout << m.ToString() << std::endl;
}
