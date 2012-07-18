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
#include "server/zone/objects/tangible/wearables/ArmorObject.h"

class WearablesDeltaVector : public DeltaVector<ManagedReference<TangibleObject*> > {
protected:
	VectorMap<uint8, Vector<ManagedReference<ArmorObject*> > > protectionArmorMap;

public:
	WearablesDeltaVector() : DeltaVector<ManagedReference<TangibleObject*> >() {
		protectionArmorMap.setAllowOverwriteInsertPlan();

		addSerializableVariable("protectionArmorMap", &protectionArmorMap);
	}

	void insertItemToMessage(ManagedReference<TangibleObject*>* item, BaseMessage* msg) {
		TangibleObject* object = item->get();

		String custString;
		object->getCustomizationString(custString);

		msg->insertAscii(custString);
		msg->insertInt(object->getContainmentType()); //Equipped
		msg->insertLong(object->getObjectID()); //object id
		msg->insertInt(object->getClientObjectCRC()); //CRC of the object
	}

	bool add(ManagedReference<TangibleObject*> element, DeltaMessage* message = NULL, int updates = 1) {
		if (element->isArmorObject()) {
			ManagedReference<ArmorObject*> armor = cast<ArmorObject*>(element.get());
			uint8 hitLocations = armor->getHitLocation();

			if (hitLocations & 0x01)
				addArmor(0x01, armor);

			if (hitLocations & 0x02)
				addArmor(0x02, armor);

			if (hitLocations & 0x04)
				addArmor(0x04, armor);

			if (hitLocations & 0x08)
				addArmor(0x08, armor);
		}

		return DeltaVector<ManagedReference<TangibleObject*> >::add(element, message, updates);
	}

	bool remove(int index, DeltaMessage* message = NULL, int updates = 1) {
		ManagedReference<TangibleObject*> element = get(index);

		if (element->isArmorObject()) {
			ManagedReference<ArmorObject*> armor = cast<ArmorObject*>(element.get());
			uint8 hitLocations = armor->getHitLocation();

			if (hitLocations & 0x01)
				removeArmor(0x01, armor);

			if (hitLocations & 0x02)
				removeArmor(0x02, armor);

			if (hitLocations & 0x04)
				removeArmor(0x04, armor);

			if (hitLocations & 0x08)
				removeArmor(0x08, armor);
		}

		return DeltaVector<ManagedReference<TangibleObject*> >::remove(index, message, updates);
	}

	Vector<ManagedReference<ArmorObject*> > getArmorAtHitLocation(uint8 hl) {
		return protectionArmorMap.get(hl);
	}

	void addArmor(uint8 hitLocation, ManagedReference<ArmorObject*> armor) {
		Vector<ManagedReference<ArmorObject*> > armors = protectionArmorMap.get(hitLocation);
		armors.add(armor);

		protectionArmorMap.drop(hitLocation);
		protectionArmorMap.put(hitLocation, armors);
	}

	void removeArmor(uint8 hitLocation, ManagedReference<ArmorObject*> armor) {
		Vector<ManagedReference<ArmorObject*> > armors = protectionArmorMap.get(hitLocation);
		armors.removeElement(armor);

		protectionArmorMap.drop(hitLocation);
		protectionArmorMap.put(hitLocation, armors);
	}
};


#endif /* WEARABLESDELTAVECTOR_H_ */
