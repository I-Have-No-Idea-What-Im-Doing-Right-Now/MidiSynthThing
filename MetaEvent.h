//
// Created by Leo Pilcher on 7/13/26.
//

#ifndef MIDISYNTH_METAEVENT_H
#define MIDISYNTH_METAEVENT_H

#include "TrackEvent.h"
#include <vector>

enum MetaEventType {
	SequenceNumber = 0,
		TextEvent = 1,
		CopyrightNotice = 2,
		TrackName = 3,
		InstrumentName = 4,
		Lyric = 5,
		Marker = 6,
		CuePoint = 7,
		MidiChannelPrefix = 32,
		TrackEnd = 47,
		SetTempo = 81,
		SmpteOffset = 84,
		TimeSignature = 88,
		KeySignature = 89,
		SequencerSpecific = 127
};

class MetaEvent : TrackEvent {
	public:
		MetaEvent(int offset, MetaEventType metaEventType, const std::vector<uint8_t>& data);
		MetaEvent(int offset, int metaEventType, const std::vector<uint8_t>& data);
		[[nodiscard]] std::string ToString() const;

		MetaEventType metaType;
		std::vector<uint8_t> data;
};


#endif //MIDISYNTH_METAEVENT_H
