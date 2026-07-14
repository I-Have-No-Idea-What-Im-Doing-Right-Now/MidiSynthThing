//
// Created by Leo Pilcher on 7/14/26.
//

#ifndef MIDISYNTH_MIDITRACK_H
#define MIDISYNTH_MIDITRACK_H
#include <vector>
#include <memory>
#include "MidiEvent.h"
#include "TrackEvent.h"

using namespace TrackEvents;

class MidiTrack {
	public:
		MidiTrack();
		MidiTrack(const MidiTrack& track);
		explicit MidiTrack(const std::vector<std::shared_ptr<TrackEvent>>& events);

		std::vector<std::shared_ptr<TrackEvent>> events;

	private:
		void AddEvent(MidiEvent& event);
};

#endif //MIDISYNTH_MIDITRACK_H
