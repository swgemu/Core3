/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WAYPOINTLIST_H_
#define WAYPOINTLIST_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

class WaypointList : public DeltaVectorMap<uint64, ManagedReference<WaypointObject*> > {
public:

	int set(uint64 key, WaypointObject* value, DeltaMessage* message = nullptr, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != nullptr) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return pos;
	}

	friend void to_json(nlohmann::json& j, const WaypointList& w) {
		const DeltaVectorMap<uint64, ManagedReference<WaypointObject*> >& vm = w;

		to_json(j, vm);
	}

	bool drop(const uint64& key, DeltaMessage* message = nullptr, int updates = 1) override {
		if (!vectorMap.contains(key))
			return false;

		ManagedReference<WaypointObject*> value = vectorMap.get(key);

		vectorMap.drop(key);

		if (message != nullptr) {
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

		if (message != nullptr) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(2);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return true;
	}

	void insertToMessage(BaseMessage* msg) const override {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		for (int i = 0; i < size(); ++i) {
			const uint64& key = getKeyAt(i);
			const auto& value = getValueAt(i);

			msg->insertByte(0);
			msg->insertLong(key);
			value->insertToMessage(msg);
		}
	}

	uint64 find(const String& name) const {
		if (name.isEmpty())
			return 0;

		for (int i = 0; i < size(); ++i) {
			const uint64& key = getKeyAt(i);
			const auto& value = getValueAt(i);

			if (name == value->getCustomObjectName().toString())
				return key;
		}

		return 0;
	}

	uint64 getWaypointBySpecialType(const uint8 specialTypeID) const {
		if (specialTypeID == 0)
			return 0;

		for (int i = 0; i < vectorMap.size(); ++i) {
			const auto& value = vectorMap.elementAt(i).getValue();

			if (value->getSpecialTypeID() == specialTypeID)
				return value->getObjectID();
		}

		return 0;
	}

	WaypointObject* getWaypointAt(float x, float y, String planet) const {
		for (int i = 0; i < vectorMap.size(); ++i) {
			const auto& value = vectorMap.elementAt(i).getValue();

			if (value->getPositionX() == x && value->getPositionY() == y && value->getPlanetCRC() == planet.hashCode())
				return value;
		}

		return nullptr;
	}
};


#endif /* WAYPOINTLIST_H_ */
