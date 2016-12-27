/*
 * HopperMap.h
 *
 *  Created on: 11/06/2010
 *      Author: victor
 */

#ifndef HOPPERMAP_H_
#define HOPPERMAP_H_

#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/resource/ResourceContainer.h"

class HopperList : public DeltaVector<ManagedReference<ResourceContainer*> > {
public:

	ManagedReference<ResourceContainer*> set(int idx, const ManagedReference<ResourceContainer*>& newValue, DeltaMessage* message = NULL, int updates = 1) {
		ManagedReference<ResourceContainer*> object = vector.set(idx, newValue);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(2);
			message->insertShort(idx);

			message->insertLong(newValue->getSpawnObject()->getObjectID());
			message->insertFloat(newValue->getQuantity());
		}

		return object;
	}

	bool add(const ManagedReference<ResourceContainer*>& element, DeltaMessage* message = NULL, int updates = 1) {
		bool val = vector.add(element);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);
			message->insertShort(vector.size() - 1);

			message->insertLong(element->getSpawnObject()->getObjectID());
			message->insertFloat(element->getQuantity());
		}

		return val;
	}

	void insertToMessage(BaseMessage* msg) {
		msg->insertInt(size());
		msg->insertInt(updateCounter);

		for (int i = 0; i < size(); ++i) {
			ResourceContainer* value = get(i);

			msg->insertLong(value->getSpawnObject()->getObjectID());
			msg->insertFloat(value->getQuantity());
		}
	}
};


#endif /* HOPPERMAP_H_ */
