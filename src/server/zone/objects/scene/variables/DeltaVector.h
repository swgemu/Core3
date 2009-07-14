/*
 * DeltaVector.h
 *
 *  Created on: 13/07/2009
 *      Author: TheAnswer
 */

#ifndef DELTALIST_H_
#define DELTALIST_H__H_

#include "engine/engine.h"


template <class E> class DeltaVector : public Serializable {
	Vector<E> vector;
	uint32 updateCounter;

public:
	DeltaVector() : Serializable() {
		updateCounter = 0;

		addSerializableVariables();
	}

	void addSerializableVariables() {
		addSerializableVariable("vector", &vector);
		addSerializableVariable("updateCounter", &updateCounter);
	}

	bool add(const E& element, bool updateCounter = true) {
		++updateCounter;
		return vector.add(element);
	}

	bool add(int index, const E& element, bool updateCounter = true) {
		++updateCounter;
		return vector.add(index, element);
	}

	E& get(int index) const {
		return vector.get(index);
	}

	E remove(int index, bool updateCounter = true) {
		++updateCounter;
		return vector.remove(index);
	}

	void removeAll(bool updateCounter = true) {
		++updateCounter;
		vector.removeAll();
	}

	E set(int index, const E& element, bool updateCounter = true) {
		++updateCounter;
		return vector.set(index, element);
	}

};


#endif /* DELTAVECTOR_H_ */
