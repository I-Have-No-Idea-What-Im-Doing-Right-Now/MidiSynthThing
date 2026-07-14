#include "TrackEvent.h"
namespace TrackEvents {
	TrackEvent::TrackEvent(EventType eventType, int offset) {
		trackEventType = eventType;
		eventOffset = offset;
	}

	TrackEvent::TrackEvent(int eventType, int offset) {
		trackEventType = static_cast<EventType>(eventType);
		eventOffset = offset;
	}
}