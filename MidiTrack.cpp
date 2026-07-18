//
// Created by Leo Pilcher on 7/14/26.
//

#include "MidiTrack.h"
#include "utils.h"
#include <format>
#include <memory>
#include "MetaEvent.h"
#include "MidiEvent.h"

MidiTrack::MidiTrack() = default;

MidiTrack::MidiTrack(const MidiTrack &track) {
	events = track.events;
}
MidiTrack::MidiTrack(const std::vector<std::shared_ptr<TrackEvent>>& trackEvents) {
	events = trackEvents;
}

MidiTrack::MidiTrack(const std::vector<TrackEvent*> &trackEvents) {
	for (const TrackEvent* trackEvent : trackEvents) {
		AddEvent(*trackEvent);
	}
}

MidiTrack::MidiTrack(const std::vector<TrackEvent>& trackEvents) {
	for (const TrackEvent& trackEvent : trackEvents) {
		AddEvent(trackEvent);
	}
}

MidiTrack::MidiTrack(const std::vector<uint8_t>& data) {
	int position = 0; // Keep track of position

	while (position < data.size()) {
		// Get offset of the event
		auto [offset, offsetLen] = DecodeVariableLength(std::vector<uint8_t>(data.begin() + position, data.end()));
		position += offsetLen;

		// Parse the event data:

		// Sysex events
		if (data[position] == 240) { // Check for starting byte of a sysex event
			while (data[position] != 247) position++; // Skip until end byte is reached
			position++;
			continue; // Start loop again to get offset for next event
		}

		// Meta Events
		if (data[position] == 255) {
			position++;
			const auto metaType = static_cast<MetaEventType>(data[position]); // Get the meta event's type
			position++;

			// Get the length value for the data of the meta event and the length of the length value
			auto [length, lengthLength] = DecodeVariableLength(std::vector<uint8_t>(data.begin() + position, data.end()));
			position += lengthLength;
			std::vector eventData(data.begin() + position, data.begin() + position + length);

			MetaEvent event(offset, metaType, eventData);
			AddEvent(event);
			position += length; // Move over data of the meta event
			if (metaType == MetaEventType::trackEnd) break;
		}

		// Midi events
		else {
			// Mask out last 4 bits of the first byte of the Midi event to get channel number
			auto channel = data[position] & 15;

			// Bitwise AND with 240 (11110000) to mask out first 4 bits and bitshift to put at start of byte
			auto eventType = static_cast<MidiEventType>((data[position] & 240) >> 4);

			position += 1;
			const int eventDataLength = midiEventDataLengths[eventType];
			std::vector eventData(data.begin() + position, data.begin() + position + eventDataLength);
			position += eventDataLength;

			MidiEvent event(offset, eventType, channel, eventData);
			AddEvent(event);
		}
	}
}


void MidiTrack::AddEvent(const TrackEvent& event) {
	std::unique_ptr<TrackEvent> uniqueCopy = event.Clone();
	const std::shared_ptr<TrackEvent> sharedCopy = std::move(uniqueCopy);
	events.push_back(sharedCopy);
}

std::pair<int, int> MidiTrack::DecodeVariableLength(const std::vector<uint8_t> &data) {
	int value = 0;
	int variableLen = 1;
	while (true) {
		if (variableLen > data.size()) {
			throw std::out_of_range("Reached the end of provided data without finding non-escaped final byte of variable length data");
		}
		value *= 256;
		value += data[variableLen - 1] & 127; // Bitwise AND to mask escape bit
		if (data[variableLen - 1] < 128) break;
		variableLen++;
	}
	return {value, variableLen};
}

std::string MidiTrack::ToString() const {
	std::string contents;
	for (const auto& trackEvent : events) {
		contents.append(trackEvent->ToString());
		contents.append("\n");
	}
	return std::format("Midi Track:\n{}", indent_string(contents));
}
