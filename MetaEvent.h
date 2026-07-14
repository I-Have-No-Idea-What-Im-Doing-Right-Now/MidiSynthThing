//
// Created by Leo Pilcher on 7/13/26.
//

#ifndef MIDISYNTH_METAEVENT_H
#define MIDISYNTH_METAEVENT_H

#include "TrackEvent.h"
#include <vector>

namespace TrackEvents {
	enum class MetaEventType {
		sequenceNumber = 0,
		textEvent = 1,
		copyrightNotice = 2,
		trackName = 3,
		instrumentName = 4,
		lyric = 5,
		marker = 6,
		cuePoint = 7,
		midiChannelPrefix = 32,
		trackEnd = 47,
		setTempo = 81,
		smpteOffset = 84,
		timeSignature = 88,
		keySignature = 89,
		sequencerSpecific = 127
	};

	class MetaEvent : TrackEvent {
	public:
		MetaEvent(int offset, MetaEventType metaEventType, const std::vector<uint8_t>& data);
		MetaEvent(int offset, int metaEventType, const std::vector<uint8_t>& data);
		[[nodiscard]] std::string ToString() const;

		MetaEventType metaType;
		std::vector<uint8_t> data;
	};
}
#endif //MIDISYNTH_METAEVENT_H
