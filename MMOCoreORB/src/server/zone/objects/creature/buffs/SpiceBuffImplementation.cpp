/*
 * SpiceBuffImplementation.cpp
 *
 *  Created on: 15/08/2010
 *      Author: victor
 */

#include "server/zone/objects/creature/buffs/SpiceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/events/SpiceDownerAnimationTask.h"
#include "server/zone/objects/creature/buffs/SpiceDownerBuff.h"

void SpiceBuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(true);

	if (removeModifiers) {
		//StackTrace::printStackTrace();
		//info("activating downer", true);
		uint32 crc = String("spice." + buffName + ".down").hashCode();
		ManagedReference<Buff*> downer = new SpiceDownerBuff(creature.get(), buffName, crc, 120);
		setDownerAttributes(creature.get(), downer);
		creature.get()->addBuff(downer);

		// Puke now and every 15 seconds while debuff is active
		creature.get()->doAnimation("heavy_cough_vomit");
		Reference<Task*> downerAnimationTask = new SpiceDownerAnimationTask( creature.get(), crc);
		creature.get()->addPendingTask("spice_downer_animation", downerAnimationTask, 15000);
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
