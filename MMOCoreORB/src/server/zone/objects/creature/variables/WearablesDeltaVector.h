/*
 * WearablesDeltaVector.h
 *
 *  Created on: 09/04/2012
 *      Author: victor
 */

#ifndef WEARABLESDELTAVECTOR_H_
#define WEARABLESDELTAVECTOR_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class WearablesDeltaVector : public DeltaVector<ManagedReference<TangibleObject*> > {
public:
	void insertItemToMessage(ManagedReference<TangibleObject*>* item, BaseMessage* msg) {
		TangibleObject* object = item->get();

		String custString;
		object->getCustomizationString(custString);

		msg->insertAscii(custString);
		msg->insertInt(object->getContainmentType()); //Equipped
		msg->insertLong(object->getObjectID()); //object id
		msg->insertInt(object->getClientObjectCRC()); //CRC of the object
	}
};


#endif /* WEARABLESDELTAVECTOR_H_ */
