//
// Created by Leo Pilcher on 7/14/26.
//

#include "MidiTrack.h"
#include "utils.h"
#include <format>
#include <iostream>
#include <memory>

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

void MidiTrack::AddEvent(const TrackEvent& event) {
	std::unique_ptr<TrackEvent> uniqueCopy = event.Clone();
	const std::shared_ptr<TrackEvent> sharedCopy = std::move(uniqueCopy);
	events.push_back(sharedCopy);
}

std::string MidiTrack::ToString() const {
	std::string contents;
	for (const auto& trackEvent : events) {
		contents.append(trackEvent->ToString());
		contents.append("\n");
	}
	return std::format("Midi Track:\n{}", indent_string(contents));
}
