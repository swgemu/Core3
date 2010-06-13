/*
 * HopperEntry.h
 *
 *  Created on: 12/06/2010
 *      Author: victor
 */

#ifndef HOPPERENTRY_H_
#define HOPPERENTRY_H_

#include "server/zone/objects/resource/ResourceContainer.h"

class HopperEntry : public Variable {
protected:
	ManagedReference<ResourceContainer*> resource;
	float quantity;

public:

	HopperEntry()  : Variable() {
		resource = NULL;
		quantity = 0;
	}

	HopperEntry(const HopperEntry& entry) : Variable() {
		resource = entry.resource;
		quantity = entry.quantity;
	}

	HopperEntry& operator=(const HopperEntry& entry) {
		if (this == &entry)
			return *this;

		resource = entry.resource;
		quantity = entry.quantity;
	}

	bool toString(String& str) {
		resource.toString(str);
		TypeInfo<float>::toString(&quantity, str);

		return true;
	}

	bool parseFromString(const String& str, int version = 0) {
		resource.parseFromString(str, version);
		TypeInfo<float>::parseFromString(&quantity, str);
		return true;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		resource.toBinaryStream(stream);
		TypeInfo<float>::toBinaryStream(&quantity, stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		resource.parseFromBinaryStream(stream);
		TypeInfo<float>::parseFromBinaryStream(&quantity, stream);

		return true;
	}

	float getQuantity() const {
		return quantity;
	}

	ResourceContainer* getResource() const {
		return resource;
	}

	void setQuantity(float quantity) {
		this->quantity = quantity;
	}

	void setResource(ResourceContainer* resource) {
		this->resource = resource;
	}
};

#endif /* HOPPERENTRY_H_ */
