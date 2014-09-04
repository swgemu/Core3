
#ifndef EVENTPERKDATACOMPONENT_H_
#define EVENTPERKDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"

class EventPerkDataComponent : public DataObjectComponent {
protected:
	ManagedReference<EventPerkDeed*> deed;

public:
	EventPerkDataComponent() {

	}

	virtual ~EventPerkDataComponent() {

	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		int _currentOffset = stream->getOffset();
		stream->writeShort(0);
		int _varCount = writeObjectMembers(stream);
		stream->writeShort(_currentOffset, _varCount);

		return true;
	}

	int writeObjectMembers(ObjectOutputStream* stream) {
		String _name;
		int _offset;
		uint32 _totalSize;

		_name = "deed";
		_name.toBinaryStream(stream);
		_offset = stream->getOffset();
		stream->writeInt(0);
		TypeInfo<ManagedReference<EventPerkDeed*> >::toBinaryStream(&deed, stream);
		_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
		stream->writeInt(_offset, _totalSize);

		return 1;
	}

	bool readObjectMember(ObjectInputStream* stream, const String& name) {
		if (name == "deed") {
			TypeInfo<ManagedReference<EventPerkDeed*> >::parseFromBinaryStream(&deed, stream);

			return true;
		}
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		uint16 _varCount = stream->readShort();

		for (int i = 0; i < _varCount; ++i) {
			String _name;
			_name.parseFromBinaryStream(stream);
			uint32 _varSize = stream->readInt();
			int _currentOffset = stream->getOffset();
			if(readObjectMember(stream, _name)) {
			}
			stream->setOffset(_currentOffset + _varSize);
		}
		return true;
	}

	void setDeed(EventPerkDeed* de) {
		deed = de;
	}

	EventPerkDeed* getDeed() {
		return deed;
	}

	bool isEventPerkData() {
		return true;
	}
};


#endif /* EVENTPERKDATACOMPONENT_H_ */
