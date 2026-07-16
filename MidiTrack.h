//
// Created by Leo Pilcher on 7/14/26.
//

#ifndef MIDISYNTH_MIDITRACK_H
#define MIDISYNTH_MIDITRACK_H
#include <vector>
#include <memory>
#include "TrackEvent.h"

using namespace TrackEvents;

class MidiTrack {
	public:
		MidiTrack();
		MidiTrack(const MidiTrack& track);

		explicit MidiTrack(const std::vector<std::shared_ptr<TrackEvent>>& trackEvents);
		explicit MidiTrack(const std::vector<TrackEvent*>& trackEvents);
		explicit MidiTrack(const std::vector<TrackEvent>& trackEvents);
		explicit MidiTrack(const std::vector<uint8_t>& data);

		[[nodiscard]] std::string ToString() const;

		std::vector<std::shared_ptr<TrackEvent>> events;

	private:
		void AddEvent(const TrackEvent& event);
		static std::pair<int, int> DecodeVariableLength(const std::vector<uint8_t>& data);
};

#endif //MIDISYNTH_MIDITRACK_H
