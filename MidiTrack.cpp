//
// Created by Leo Pilcher on 7/14/26.
//

#include "MidiTrack.h"
#include <memory>

MidiTrack::MidiTrack() = default;

MidiTrack::MidiTrack(const MidiTrack &track) {
	events = track.events;
}
MidiTrack::MidiTrack(const std::vector<std::shared_ptr<TrackEvent>>& events) {
	this->events = events;
}

void MidiTrack::AddEvent(MidiEvent& event) {
	std::unique_ptr<TrackEvent> uniqueCopy = event.Clone();
	const std::shared_ptr<TrackEvent> sharedCopy = std::move(uniqueCopy);
	events.push_back(sharedCopy);
}
