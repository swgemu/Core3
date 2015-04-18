/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WAYPOINTLIST_H_
#define WAYPOINTLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

class WaypointList : public DeltaVectorMap<uint64, ManagedReference<WaypointObject*> > {
public:

	int set(uint64 key, WaypointObject* value, DeltaMessage* message = NULL, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return pos;
	}

	bool drop(const uint64& key, DeltaMessage* message = NULL, int updates = 1) {
		if (!vectorMap.contains(key))
			return false;

		ManagedReference<WaypointObject*> value = vectorMap.get(key);

		vectorMap.drop(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return true;
	}

	bool update(const uint64& key, DeltaMessage* message, int updates = 1) {
		if (!vectorMap.contains(key))
			return false;

		ManagedReference<WaypointObject*> value = vectorMap.get(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(2);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return true;
	}

	void insertToMessage(BaseMessage* msg) {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		for (int i = 0; i < size(); ++i) {
			uint64& key = getKeyAt(i);
			ManagedReference<WaypointObject*> value = getValueAt(i);

			msg->insertByte(0);
			msg->insertLong(key);
			value->insertToMessage(msg);
		}
	}

	uint64 find(const String& name) {
		if (name.isEmpty())
			return 0;

		for (int i = 0; i < size(); ++i) {
			uint64& key = getKeyAt(i);
			ManagedReference<WaypointObject*> value = getValueAt(i);

			if (name == value->getCustomObjectName().toString())
				return key;
		}

		return 0;
	}

	uint64 getWaypointBySpecialType(const uint8 specialTypeID) {
		if (specialTypeID == 0)
			return 0;

		for (int i = 0; i < vectorMap.size(); ++i) {
			ManagedReference<WaypointObject*> value = vectorMap.elementAt(i).getValue();

			if (value->getSpecialTypeID() == specialTypeID)
				return value->getObjectID();
		}

		return 0;

	}

};


#endif /* WAYPOINTLIST_H_ */
