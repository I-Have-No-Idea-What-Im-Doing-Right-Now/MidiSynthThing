//
// Created by Leo Pilcher on 7/14/26.
//

#ifndef MIDISYNTH_MIDIEVENT_H
#define MIDISYNTH_MIDIEVENT_H

#include <unordered_map>
#include <vector>
#include "TrackEvent.h"

namespace TrackEvents {
	enum class MidiEventType {
		noteOff = 8,
		noteOn = 9,
		polyphonicKeyPressure = 10, // Pressure of key after being pressed
		controlChange = 11, // Need to do stuff with this
		programChange = 12,
		channelKeyPressure = 13, // Like poly key pressure but overall highest on channel
		pitchWheelChange = 14
	};

	std::unordered_map<MidiEventType, int> midiEventDataLengths = {
		{MidiEventType::noteOff, 2},
			{MidiEventType::noteOn, 2},
			{MidiEventType::polyphonicKeyPressure, 2},
			{MidiEventType::controlChange, 2},
			{MidiEventType::programChange, 1},
			{MidiEventType::channelKeyPressure, 1},
			{MidiEventType::pitchWheelChange, 2}
	};


	class MidiEvent : public TrackEvent {
	public:
		MidiEvent(int offset, MidiEventType eventType, int channel, const std::vector<uint8_t> &data);
		MidiEventType midiEventType;
		int channel;
		std::vector<uint8_t> data;
		[[nodiscard]] std::string ToString() const override;
		[[nodiscard]] std::unique_ptr<TrackEvent> Clone() const override;
	};
}
#endif //MIDISYNTH_MIDIEVENT_H
