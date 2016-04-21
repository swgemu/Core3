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
		BuffImplementation::activate(applyModifiers);
		attributeMods = getAttributeModifiers();

		if (cfBuffEvent != NULL) {
			cfBuffEvent->cancel();
                } else {
                  	cfBuffEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());
                }

		cfBuffEvent->schedule(secondsToUpdate * 1000);
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(removeModifiers);
	if (cfBuffEvent != NULL) {
		cfBuffEvent->cancel();
		cfBuffEvent = NULL;
	}
}

void ChannelForceBuffImplementation::doHamTick() {

  	// Locks.
  	ManagedReference<CreatureObject*> creo = creature.get();

	if (creo == NULL)
		return;

  	Locker crossLock(creo, _this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < attributeMods->size(); ++i) {
		byte attribute = attributeMods->elementAt(i).getKey();
		int modifier = attributeMods->elementAt(i).getValue();
		int healAmount = -(modifier / numberOfTicks);
		creo->addMaxHAM(attribute, healAmount, true);
		setAttributeModifier(attribute, (getAttributeModifierValue(attribute) - healAmount));
	}

	cfBuffEvent->reschedule(secondsToUpdate * 1000);
}
