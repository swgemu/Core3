#ifndef SHIPUNIQUEIDMAP_H_
#define SHIPUNIQUEIDMAP_H_

#include "engine/engine.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipUniqueIdMap : public Object, public Logger {
private:
	const static int INDEXMAX = std::numeric_limits<uint16>::max();
	const static int INDEXMIN = 1;

protected:
	VectorMap<uint16, ManagedWeakReference<ShipObject*>> shipIdMap;
	mutable ReadWriteLock mutex;
	int index;

public:
	ShipUniqueIdMap() {
		setLoggingName("ShipUniqueIdMap");

		shipIdMap.removeAll(INDEXMAX,INDEXMAX);
		shipIdMap.setNoDuplicateInsertPlan();
		shipIdMap.setNullValue(nullptr);

		shipIdMap.put(0, nullptr);
		index = INDEXMIN;
	}

	uint16 getUniqueID() {
		Locker mLock(&mutex);

		for (uint16 shipID = index; shipID < INDEXMAX; ++shipID) {
			auto entry = shipIdMap.get(shipID);

			if (entry == nullptr) {
				index = shipID + 1;
				return shipID;
			}
		}

		for (uint16 shipID = INDEXMIN; shipID < INDEXMAX; ++shipID) {
			auto entry = shipIdMap.get(shipID);

			if (entry == nullptr) {
				index = shipID + 1;
				return shipID;
			}
		}

		error() << "ShipUniqueIdMap::getUniqueID: failed to resolve a valid ID at map size: " << shipIdMap.size();
		return 0;
	}

	uint16 setUniqueID(ShipObject* ship) {
		if (ship == nullptr) {
			return 0;
		}

		Locker mLock(&mutex);
		uint16 shipID = getUniqueID();

		if (shipID != 0) {
			shipIdMap.put(shipID, ship);
		}

		return shipID;
	}

	void dropUniqueID(ShipObject* ship) {
		if (ship == nullptr) {
			return;
		}

		Locker mLock(&mutex);
		uint16 shipID = ship->getUniqueID();

		if (shipID != 0 && shipIdMap.get(shipID) == ship) {
			shipIdMap.drop(shipID);
		}
	}
};

#endif // SHIPUNIQUEIDMAP_H_
