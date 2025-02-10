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

	DeltaSet& operator=(const DeltaSet& ds) {
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

	virtual int add(const K& key, const V& value, DeltaMessage* message = nullptr, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != nullptr) {
			if (updates != 0) {
				message->startList(updates, updateCounter += updates);
			}

			message->insertByte(0x01);

			K& nonconstK = const_cast<K&>(key);
			TypeInfo<K>::toBinaryStream(&nonconstK, message);
		}

		return pos;
	}

	virtual bool drop(const K& key, DeltaMessage* message = nullptr, int updates = 1) {
		if (!vectorMap.contains(key)) {
			return false;
		}

		V& value = vectorMap.get(key);

		vectorMap.drop(key);

		// Increase update Counter
		updateCounter += updates;

		if (message != nullptr) {
			if (updates != 0) {
				message->startList(updates, updateCounter += updates);
			}

			message->insertByte(0x00);

			TypeInfo<K>::toBinaryStream(const_cast<K*>(&key), message);
		}

		return true;
	}

	virtual int addWithKey(const K& key, const V& value, DeltaMessage* message = nullptr, int updates = 1) {
		int pos = vectorMap.put(key, value);

		// Increase update Counter
		updateCounter += updates;

		if (message != nullptr) {
			message->startList(updates, updateCounter);

			message->insertByte(0x01);

			TypeInfo<K>::toBinaryStream(const_cast<K*>(&key), message);
			TypeInfo<V>::toBinaryStream(const_cast<V*>(&value), message);
		}

		return pos;
	}

	virtual bool dropByValue(const K& removeKey, const V& removeValue, DeltaMessage* message = nullptr, int updates = 1) {
		for (int i = size() - 1; i >= 0; i--) {
			const K& key = getKeyAt(i);
			const V& value = getValueAt(i);

			if (key != removeKey || value != removeValue) {
				continue;
			}

			vectorMap.removeElementAt(i);

			// Increase update Counter
			updateCounter += updates;

			if (message != nullptr) {
				message->startList(updates, updateCounter);

				message->insertByte(0x0);

				TypeInfo<K>::toBinaryStream(const_cast<K*>(&key), message);
				TypeInfo<V>::toBinaryStream(const_cast<V*>(&value), message);
			}

			return true;
		}

		return false;
	}

	virtual void removeAll(DeltaMessage* msg) {
		vectorMap.removeAll();

		if (msg != nullptr) {
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

	virtual void insertKeyAndValuesToMessage(BaseMessage* msg) {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		for (int i = 0; i < size(); ++i) {
			msg->insertByte(0x01);

			const K& key = getKeyAt(i);
			const V& value = getValueAt(i);

			TypeInfo<K>::toBinaryStream(const_cast<K*>(&key), msg);
			TypeInfo<V>::toBinaryStream(const_cast<V*>(&value), msg);
		}
	}

	inline void setNullValue(const V& val) {
		vectorMap.setNullValue(val);
	}

	inline void setAllowDuplicateInsert() {
		vectorMap.setAllowDuplicateInsertPlan();
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

	inline bool containsValue(const V& value) {
		for (int i = 0; i < vectorMap.size(); i++) {
			if (vectorMap.elementAt(i).getValue() != value) {
				continue;
			}

			return true;
		}

		return false;
	}

	inline int size() const {
		return vectorMap.size();
	}

	inline uint32 getUpdateCounter() const {
		return updateCounter;
	}
};

#endif /* DELTASET_H_ */
