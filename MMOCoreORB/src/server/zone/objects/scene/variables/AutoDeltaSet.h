/*
 * AutoDeltaSet.h
 *
 *  Created on: Apr 1, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_AUTODELTASET_H_
#define SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_AUTODELTASET_H_

#include "engine/engine.h"
#include "system/util/HashSet.h"

#include "server/zone/packets/DeltaMessage.h"

template <class K>
class AutoDeltaSet : public Variable {
protected:
	HashSet<K> set;
	uint32 updateCounter;

public:
	AutoDeltaSet() : Variable() {
		updateCounter = 0;
	}

	AutoDeltaSet(int initcap) : Variable(), set(initcap) {
		updateCounter = 0;
	}

	AutoDeltaSet(const AutoDeltaSet& ds) : Variable(), set(ds.set) {
		updateCounter = ds.updateCounter;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		stream->writeInt(updateCounter);

		return set.toBinaryStream(stream);
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		updateCounter = stream->readInt();

		return set.parseFromBinaryStream(stream);
	}

	virtual void add(const K& key, DeltaMessage* message = NULL, int updates = 1) {
		set.add(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);

			K& nonconstK = const_cast<K&>(key);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
		}
	}

	virtual bool drop(const K& key, DeltaMessage* message = NULL, int updates = 1) {
		if (!set.contains(key))
			return false;

		set.remove(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);

			K& nonconstK = const_cast<K&>(key);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
		}

		return true;
	}

	virtual void removeAll(DeltaMessage* msg = NULL) {
		set.removeAll();

		if (msg != NULL) {
			msg->startList(1, ++updateCounter);
			msg->insertByte(2);
		}
	}

	virtual void insertToMessage(BaseMessage* msg) {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		HashSetIterator<K> iterator = set.iterator();

		while (iterator.hasNext()) {
			K& key = iterator.next();

			TypeInfo<K>::toBinaryStream(&key, msg);
		}
	}

	inline bool contains(const K& key) {
		return set.contains(key);
	}

	inline int size() {
		return set.size();
	}

	inline uint32 getUpdateCounter() {
		return updateCounter;
	}

	inline HashSetIterator<K> getIterator() {
		return set.iterator();
	}
};


#endif /* SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_AUTODELTASET_H_ */
