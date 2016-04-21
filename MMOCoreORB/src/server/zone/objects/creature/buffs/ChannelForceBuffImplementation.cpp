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
		// Generic buff activate.
		BuffImplementation::activate(true);

		if (cfBuffEvent != NULL) {
			cfBuffEvent->cancel();
                } else {
                  	cfBuffEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());
                }

		cfBuffEvent->schedule(8000);
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(true);
	if (cfBuffEvent != NULL) {
		cfBuffEvent->cancel();
		cfBuffEvent = NULL;
	}
}

void ChannelForceBuffImplementation::doHamTick() {

	// Grab what the attribute modifiers have.
	VectorMap<byte, int>* attributeModifiers = getAttributeModifiers();

  	int divisor = 20; // Dividing the attribute modifier by this amount.
  	int secondsToUpdate = 8; // In seconds.

  	// Locks.
  	Locker locker(creatureObject);
  	Locker crossLock(creatureObject, _this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < attributeModifiers->size(); ++i) {
		byte attribute = attributeModifiers->elementAt(i).getKey();
		int modifier = attributeModifiers->elementAt(i).getValue();
		int healAmount = MAX(-modifier / divisor, -modifier);
		creatureObject->addMaxHAM(attribute, healAmount, true);
		setAttributeModifier(attribute, modifier + healAmount);
	}

	cfBuffEvent->reschedule(secondsToUpdate * 1000);
}
