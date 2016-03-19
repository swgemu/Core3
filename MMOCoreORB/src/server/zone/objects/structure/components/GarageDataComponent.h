/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GARAGEDATACOMPONENT_H_
#define GARAGEDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "system/util/SynchronizedSortedVector.h"

class GarageDataComponent : public DataObjectComponent {
protected:
	SynchronizedSortedVector<uint64> notifiedPlayers;

public:
	GarageDataComponent() {

	}

	~GarageDataComponent() {

	}

	bool hasNotifiedPlayer(const uint64 oid) {
		return notifiedPlayers.contains(oid);
	}

	void addNotifiedPlayer(const uint64 oid) {
		notifiedPlayers.put(oid);
	}

	void removeNotifiedPlayer(const uint64 oid) {
		notifiedPlayers.drop(oid);
	}
};

#endif /* GARAGEDATACOMPONENT_H_ */
