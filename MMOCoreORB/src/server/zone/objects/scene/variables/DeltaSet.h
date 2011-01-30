/*
 * DeltaSet.h
 *
 *  Created on: 30/10/2010
 *      Author: victor
 */

#ifndef DELTASET_H_
#define DELTASET_H_

#include "engine/engine.h"
#include "server/zone/packets/DeltaMessage.h"

template <class K, class V> class DeltaSet : public Serializable {
protected:
	VectorMap<K, V> vectorMap;
	uint32 updateCounter;

public:
	DeltaSet() : Serializable() {
		updateCounter = 0;

		vectorMap.setAllowOverwriteInsertPlan();

		addSerializableVariables();
	}

	DeltaSet(int initsize, int incr) : Serializable(), vectorMap(initsize, incr) {
		updateCounter = 0;

		vectorMap.setAllowOverwriteInsertPlan();

		addSerializableVariables();
	}

	DeltaSet(const DeltaSet& ds) : Object(), Serializable() {
		updateCounter = ds.updateCounter;
		vectorMap.setAllowOverwriteInsertPlan();
		vectorMap = ds.vectorMap;

		addSerializableVariables();
	}

	inline void addSerializableVariables() {
		addSerializableVariable("vectorMap", &vectorMap);
		addSerializableVariable("updateCounter", &updateCounter);
	}

	virtual int add(const K& key, const V& value, DeltaMessage* message = NULL, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);

			K& nonconstK = const_cast<K&>(key);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
		}

		return pos;
	}

	virtual bool drop(const K& key, DeltaMessage* message = NULL, int updates = 1) {
		if (!vectorMap.contains(key))
			return false;

		V& value = vectorMap.get(key);

		vectorMap.drop(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);

			K& nonconstK = const_cast<K&>(key);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
		}

		return true;
	}

	virtual void removeAll(DeltaMessage* msg) {
		vectorMap.removeAll();

		if (msg != NULL) {
			msg->startList(1, ++updateCounter);
			msg->insertByte(2);
		}
	}

	virtual void insertToMessage(BaseMessage* msg) {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		for (int i = 0; i < size(); ++i) {
			K& key = getKeyAt(i);

			TypeInfo<K>::toBinaryStream(&key, msg);
		}
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

	inline void setNullValue(const V& val) {
		vectorMap.setNullValue(val);
	}
};

#endif /* DELTASET_H_ */
