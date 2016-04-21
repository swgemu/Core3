#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/ChannelForceBuffTickEvent.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"
#include "templates/params/creature/CreatureAttribute.h"

void ChannelForceBuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();

	if (cfBuffEvent == NULL) {
		cfBuffEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());
	}
}

void ChannelForceBuffImplementation::activate(bool applyModifiers) {
	if(creature.get() != NULL) {
		// Generic buff activate.
		BuffImplementation::activate(true);

		if (cfBuffEvent == NULL) {
			cfBuffEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());
		}

		cfBuffEvent->schedule(8000);
	}
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	if(creature.get() != NULL) {
		BuffImplementation::deactivate(true);
		if (cfBuffEvent != NULL) {
			cfBuffEvent->cancel();
			cfBuffEvent = NULL;
		}
	}
}

void ChannelForceBuffImplementation::doHamTick() {
	Locker locker(creature.get());

	// Grab what the attribute modifiers have.
	VectorMap<byte, int>* attributeModifiers = getAttributeModifiers();

	// The time-related mod.
	float mod = getTimeLeft() / 8.f;

	for (int i = 0; i < attributeModifiers->size(); ++i) {
		byte attribute = attributeModifiers->elementAt(i).getKey();
		int modifier = attributeModifiers->elementAt(i).getValue();
		int healAmount = MAX(0, -modifier/mod);
		creature.get()->addMaxHAM(attribute, healAmount, true);
		setAttributeModifier(attribute, modifier + healAmount);
	}

	if ((getAttributeModifierValue(CreatureAttribute::HEALTH) >= 0) && (getAttributeModifierValue(CreatureAttribute::ACTION) >= 0) && (getAttributeModifierValue(CreatureAttribute::MIND) >= 0)) {
		deactivate(true);
		return; // Return so it doesn't try to reschedule it.
	}

	cfBuffEvent->reschedule(8000);
}
