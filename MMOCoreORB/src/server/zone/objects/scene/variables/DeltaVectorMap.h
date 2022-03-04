/*
 * DeltaVectorMap.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef DELTAVECTORMAP_H_
#define DELTAVECTORMAP_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

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

	DeltaVectorMap(const DeltaVectorMap& ds) : Object(), Serializable() {
		updateCounter = ds.updateCounter;
		vectorMap.setAllowOverwriteInsertPlan();
		vectorMap = ds.vectorMap;

		addSerializableVariables();
	}

	DeltaVectorMap& operator=(const DeltaVectorMap& ds) {
		if (this == &ds) {
			return *this;
		}

		updateCounter = ds.updateCounter;
		vectorMap = ds.vectorMap;

		return *this;
	}

	inline void addSerializableVariables() {
		addSerializableVariable("vectorMap", &vectorMap);
		addSerializableVariable("updateCounter", &updateCounter);
	}

	friend void to_json(nlohmann::json& j, const DeltaVectorMap<K, V>& map) {
		j["vectorMap"] = map.vectorMap;
		j["updateCounter"] = map.updateCounter;
	}

	virtual int set(const K& key, const V& value, DeltaMessage* message = nullptr, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != nullptr) {
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

	virtual bool drop(const K& key, DeltaMessage* message = nullptr, int updates = 1) {
		if (!vectorMap.contains(key))
			return false;

		V& value = vectorMap.get(key);

		if (message != nullptr) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);

			K& nonconstK = const_cast<K&>(key);
			V& nonconstV = const_cast<V&>(value);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
			TypeInfo<V>::toBinaryStream(&nonconstV, message);
		}

		vectorMap.drop(key);

		return true;
	}

	virtual void insertToMessage(BaseMessage* msg) const {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		for (int i = 0; i < size(); ++i) {
			const K& key = getKeyAt(i);
			const V& value = getValueAt(i);

			msg->insertByte(0);

			TypeInfo<K>::toBinaryStream(const_cast<K*>(&key), msg);
			TypeInfo<V>::toBinaryStream(const_cast<V*>(&value), msg);
		}
	}

	inline V& getValueAt(int index) {
		return vectorMap.elementAt(index).getValue();
	}

	inline K& getKeyAt(int index) {
		return vectorMap.elementAt(index).getKey();
	}

	inline const V& getValueAt(int index) const {
		return vectorMap.elementAt(index).getValue();
	}

	inline const K& getKeyAt(int index) const {
		return vectorMap.elementAt(index).getKey();
	}

	inline V& get(const K& key) {
		return vectorMap.get(key);
	}

	inline const V& get(const K& key) const {
		return vectorMap.get(key);
	}

	inline bool contains(const K& key) const {
		return vectorMap.contains(key);
	}

	inline int size() const {
		return vectorMap.size();
	}

	inline uint32 getUpdateCounter() const {
		return updateCounter;
	}

	inline void setNullValue(const V& val) {
		vectorMap.setNullValue(val);
	}
};


#endif /* DELTAVECTORMAP_H_ */
