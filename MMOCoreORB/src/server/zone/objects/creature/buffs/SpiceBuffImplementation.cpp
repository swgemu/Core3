/*
 * SpiceBuffImplementation.cpp
 *
 *  Created on: 15/08/2010
 *      Author: victor
 */

#include "SpiceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "SpiceDownerBuff.h"

void SpiceBuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(true);

	if (removeModifiers) {
		//StackTrace::printStackTrace();
		//info("activating downer", true);
		uint32 crc = String("spice." + buffName + ".down").hashCode();
		ManagedReference<Buff*> downer = new SpiceDownerBuff(creature, buffName, crc, 120);
		setDownerAttributes(creature, downer);

		creature->addBuff(downer);
	}
}

void SpiceBuffImplementation::setDownerAttributes(CreatureObject* creature, Buff* buff) {
	for (int i = 0; i < attributeModifiers.size(); ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value <= 0)
			continue;

		int attributemax = creature->getMaxHAM(attribute) - creature->getWounds(attribute);

		int projvalue = attributemax - value;

		if (projvalue < 1)
			value += projvalue - 1;

		buff->setAttributeModifier(attribute, -value);
	}
}
