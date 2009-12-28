/*
 * DeltaVectorMap.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef DELTAVECTORMAP_H_
#define DELTAVECTORMAP_H_

#include "engine/engine.h"
#include "server/zone/packets/DeltaMessage.h"

template <class K, class V> class DeltaVectorMap : public Serializable {
protected:
	VectorMap<K, V> vectorMap;
	uint32 updateCounter;

public:
	DeltaVectorMap() : Serializable() {
		updateCounter = 1;

		vectorMap.setAllowOverwriteInsertPlan();

		addSerializableVariables();
	}

	DeltaVectorMap(int initsize, int incr) : Serializable(), vectorMap(initsize, incr) {
		updateCounter = 1;

		vectorMap.setAllowOverwriteInsertPlan();

		addSerializableVariables();
	}

	inline void addSerializableVariables() {
		addSerializableVariable("vectorMap", &vectorMap);
		addSerializableVariable("updateCounter", &updateCounter);
	}

	int set(const K& key, const V& value, DeltaMessage* message = NULL, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);

			K& nonconstK = const_cast<K&>(key);
			V& nonconstV = const_cast<V&>(value);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
			TypeInfo<V>::toBinaryStream(&nonconstV, message);
		}

		return pos;
	}

	bool drop(const K& key, DeltaMessage* message = NULL, int updates = 1) {
		if (!vectorMap.contains(key))
			return false;

		V& value = vectorMap.get(key);

		vectorMap.drop(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);

			K& nonconstK = const_cast<K&>(key);
			V& nonconstV = const_cast<V&>(value);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
			TypeInfo<V>::toBinaryStream(&nonconstV, message);
		}

		return true;
	}

	inline V& getValueAt(int index) {
		return vectorMap.elementAt(index).getValue();
	}

	inline K& getKeyAt(int index) {
		return vectorMap.elementAt(index).getKey();
	}

	inline V& get(const K& key) {
		return vectorMap.get(key);
	}

	inline bool contains(const K& key) {
		return vectorMap.contains(key);
	}

	inline int size() {
		return vectorMap.size();
	}

	inline uint32 getUpdateCounter() {
		return updateCounter;
	}
};


#endif /* DELTAVECTORMAP_H_ */
