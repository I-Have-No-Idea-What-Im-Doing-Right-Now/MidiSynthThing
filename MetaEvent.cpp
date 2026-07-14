//
// Created by Leo Pilcher on 7/13/26.
//

#include "MetaEvent.h"
#include "TrackEvent.h"
#include "utils.h"
#include <format>

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
	"Meta Event: {}\n\t- Offset: {}\n\t- Data: \n{}",
	static_cast<int>(metaType), eventOffset, bytes_to_hex(data));
}
