//
// Created by Leo Pilcher on 7/13/26.
//

#ifndef MIDISYNTH_TRACKEVENT_H
#define MIDISYNTH_TRACKEVENT_H
#include <string>
#include <memory>

namespace TrackEvents {
	enum class EventType {
		midiEvent = 1,
		metaEvent = 2,
		sysexEvent = 3
	};

	class TrackEvent {
	public:
		TrackEvent(EventType eventType, int offset);
		TrackEvent(int eventType, int offset);
		virtual ~TrackEvent() = default;

		[[nodiscard]] virtual std::string ToString() const = 0;
		[[nodiscard]] virtual std::unique_ptr<TrackEvent> Clone() const = 0;
		EventType trackEventType;
		int eventOffset;
	};
}
#endif //MIDISYNTH_TRACKEVENT_H
