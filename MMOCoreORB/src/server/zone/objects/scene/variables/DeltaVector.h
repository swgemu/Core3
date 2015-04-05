/*
 * DeltaVector.h
 *
 *  Created on: 13/07/2009
 *      Author: TheAnswer
 */

#ifndef DELTALIST_H_
#define DELTALIST_H_

#include "engine/engine.h"
#include "server/zone/packets/DeltaMessage.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
namespace variables {

template <class E> class DeltaVector : public Serializable {
protected:
	Vector<E> vector;
	uint32 updateCounter;

	ReadWriteLock* mutex;

public:
	DeltaVector() : Serializable(), vector(1, 1) {
		updateCounter = 1;

		mutex = NULL;

		addSerializableVariables();
	}

	DeltaVector(int initsize, int incr) : Serializable(), vector(initsize, incr) {
		updateCounter = 1;

		mutex = NULL;

		addSerializableVariables();
	}

	DeltaVector(const DeltaVector& v) : Object(), Serializable() {
		vector = v.vector;
		updateCounter = v.updateCounter;

		mutex = NULL;

		addSerializableVariables();
	}

	~DeltaVector() {
		if (mutex) {
			delete mutex;
			mutex = NULL;
		}
	}

	DeltaVector& operator=(const DeltaVector& v) {
		if (this == &v)
			return *this;

		vector = v.vector;
		updateCounter = v.updateCounter;

		if (mutex) {
			delete mutex;
			mutex = NULL;
		}

		return *this;
	}

	inline void addSerializableVariables() {
		addSerializableVariable("vector", &vector);
		addSerializableVariable("updateCounter", &updateCounter);
	}

	virtual E set(int idx, const E& newValue, DeltaMessage* message = NULL, int updates = 1) {
		Locker locker(getLock());

		E object = vector.set(idx, newValue);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(2);
			message->insertShort(idx);

			E& nonconst = const_cast<E&>(newValue);
			insertItemToMessage(&nonconst, message);
		}

		return object;
	}

	virtual bool add(const E& element, DeltaMessage* message = NULL, int updates = 1) {
		Locker locker(getLock());

		bool val = vector.add(element);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);
			message->insertShort(vector.size() - 1);

			E& nonconst = const_cast<E&>(element);
			insertItemToMessage(&nonconst, message);
		}

		return val;
	}

	E& get(int index) const {
		return vector.get(index);
	}

	E getSafe(int index) {
		ReadLocker locker(getLock());

		E obj = vector.get(index);

		return obj;
	}

	E remove(int index, DeltaMessage* message = NULL, int updates = 1) {
		Locker locker(getLock());

		E object = vector.remove(index);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);
			message->insertShort((uint16)index);
		}

		return object;
	}

	void removeAll(DeltaMessage* message = NULL) {
		Locker locker(getLock());

		vector.removeAll();

		if (message != NULL) {
			message->startList(1, ++updateCounter);
			message->insertByte(4);
		}
	}

	virtual void insertToMessage(BaseMessage* msg) {
		ReadLocker locker(getLock());

		msg->insertInt(size());
		msg->insertInt(updateCounter);

		for (int i = 0; i < size(); ++i) {
			E& value = get(i);
			insertItemToMessage(&value, msg);
		}
	}

	virtual void insertItemToMessage(E* item, BaseMessage* msg) {
		TypeInfo<E>::toBinaryStream(item, msg);
	}

	virtual bool contains(const E& element) {
		return find(element) != -1;
	}

	int find(const E& element) {
		for (int i = 0; i < size(); ++i) {
			if (element == get(i))
				return i;
		}

		return -1;
	}

	inline uint32 getUpdateCounter() {
		return updateCounter;
	}

	inline uint32 getNewUpdateCounter(int increment) {
		return updateCounter += increment;
	}

	inline void setUpdateCounter(int count) {
		updateCounter = count;
	}

	inline void resetUpdateCounter() {
		updateCounter = 0;
	}

	inline int size() {
		return vector.size();
	}

	inline ReadWriteLock* getLock() {
		if (mutex == NULL) {
			mutex = new ReadWriteLock();
		}

		return mutex;
	}

};


}
}
}
}
}

using namespace server::zone::objects::scene::variables;


#endif /* DELTAVECTOR_H_ */
