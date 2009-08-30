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
	Vector<E> vector;
	uint32 updateCounter;

public:
	DeltaVector() : Serializable() {
		updateCounter = 1;

		addSerializableVariables();
	}

	DeltaVector(int initsize, int incr) : Serializable(), vector(initsize, incr) {
		updateCounter = 1;

		addSerializableVariables();
	}

	inline void addSerializableVariables() {
		addSerializableVariable("vector", &vector);
		addSerializableVariable("updateCounter", &updateCounter);
	}

	E set(int idx, const E& newValue, DeltaMessage* message = NULL, int updates = 1) {
		E object = vector.set(idx, newValue);

		if (message != NULL) {
			if (updates != 0)
				message->startList(1, updateCounter += updates);

			message->insertByte(2);
			message->insertShort(idx);

			E oldElement = newValue;
			TypeInfo<E>::toBinaryStream(&oldElement, message);
		}

		return object;
	}

	bool add(const E& element, DeltaMessage* message = NULL) {
		bool val = vector.add(element);

		if (message != NULL) {
			message->startList(1, ++updateCounter);

			message->insertByte(1);
			message->insertShort(vector.size() - 1);

			E oldElement = element;
			TypeInfo<E>::toBinaryStream(&oldElement, message);
		}

		return val;
	}

	E& get(int index) const {
		return vector.get(index);
	}

	E remove(int index, DeltaMessage* message = NULL) {
		E object = vector.remove(index);

		if (message != NULL) {
			message->startList(1, ++updateCounter);

			message->insertByte(0);
			message->insertShort((uint16)index);
		}

		return object;
	}

	void removeAll(DeltaMessage* message = NULL) {
		vector.removeAll();

		if (message != NULL) {
			message->startList(1, ++updateCounter);
			message->insertByte(4);
		}
	}

	inline uint32 getUpdateCounter() {
		return updateCounter;
	}

	inline uint32 getNewUpdateCounter(int increment) {
		return updateCounter += increment;
	}

	inline int size() {
		return vector.size();
	}

};


}
}
}
}
}

using namespace server::zone::objects::scene::variables;


#endif /* DELTAVECTOR_H_ */
