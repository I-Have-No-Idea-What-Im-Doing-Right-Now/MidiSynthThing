//
// Created by Leo Pilcher on 7/13/26.
//

#include "MetaEvent.h"
#include "TrackEvent.h"
#include "utils.h"
#include <format>

namespace TrackEvents {
	MetaEvent::MetaEvent(int offset, MetaEventType metaEventType, const std::vector<uint8_t>& data) :
	TrackEvent(EventType::metaEvent, offset) {
		metaType = metaEventType;
		this->data = data;
	}

	MetaEvent::MetaEvent(int offset, int metaEventType, const std::vector<uint8_t>& data) :
	TrackEvent(EventType::metaEvent, offset) {
		metaType = static_cast<MetaEventType>(metaEventType);
		this->data = data;
	}

	std::string MetaEvent::ToString() const {
		return std::format(
		"Meta Event: {}\n\t- Offset: {}\n\tData: \n{}",
		static_cast<int>(metaType), eventOffset, indent_string(bytes_to_hex(data)));
	}
}

std::unique_ptr<TrackEvents::TrackEvent> TrackEvents::MetaEvent::Clone() const {
	return std::make_unique<MetaEvent>(*this);
}