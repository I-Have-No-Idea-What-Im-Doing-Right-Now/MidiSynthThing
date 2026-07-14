//
// Created by Leo Pilcher on 7/13/26.
//

#ifndef MIDISYNTH_TRACKEVENT_H
#define MIDISYNTH_TRACKEVENT_H

enum EventType {
	MidiEvent = 1,
	MetaEvent = 2,
	SysexEvent = 3
};

class TrackEvent {
	public:
		TrackEvent(EventType eventType, int offset);
		TrackEvent(int eventType, int offset);
		virtual ~TrackEvent() = default;
		EventType trackEventType;
		int eventOffset;
};


#endif //MIDISYNTH_TRACKEVENT_H
