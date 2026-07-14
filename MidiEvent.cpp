//
// Created by Leo Pilcher on 7/14/26.
//

#include "MidiEvent.h"
#include <format>
#include "utils.h"

namespace TrackEvents {
	MidiEvent::MidiEvent(int offset, MidiEventType eventType, int channel, const std::vector<uint8_t>& data) :
	TrackEvent(EventType::midiEvent, offset) {
		midiEventType = eventType;
		this->channel = channel;
		this->data = data;
	}

	std::string MidiEvent::ToString() const {
		return std::format("Midi Event {} on channel {}\n\tData:\n{}",
			static_cast<int>(midiEventType), channel, indent_string(bytes_to_hex(data)));
	}
}