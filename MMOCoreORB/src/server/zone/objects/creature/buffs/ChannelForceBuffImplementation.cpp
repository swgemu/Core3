#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/buffs/ChannelForceBuffTickEvent.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

void ChannelForceBuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();
}

void ChannelForceBuffImplementation::activate(bool applyModifiers) {
	if(creature.get() != NULL) {

		// Do the subtraction of max ham.
		creature.get()->addMaxHAM(CreatureAttribute::HEALTH, -cfTick, true);
		creature.get()->addMaxHAM(CreatureAttribute::ACTION, -cfTick, true);
		creature.get()->addMaxHAM(CreatureAttribute::MIND, -cfTick, true);

		// Generic buff activate.
		BuffImplementation::activate(false);

		doHamTick();
	}
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	if(creature.get() != NULL) {
		BuffImplementation::deactivate(false);
		if (amountOfTicks > 0) { // Probably got here prematurely, like a death.
			PlayerManager* pMan = creature.get()->getZoneServer()->getPlayerManager();
			if (pMan != NULL) {
				pMan->fixHAM(creature.get());
				amountOfTicks = 0;
			}
		}
	}
}

void ChannelForceBuffImplementation::doHamTick() {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());

	creature.get()->addMaxHAM(CreatureAttribute::HEALTH, cfTick / 20, true);
	creature.get()->addMaxHAM(CreatureAttribute::ACTION, cfTick / 20, true);
	creature.get()->addMaxHAM(CreatureAttribute::MIND, cfTick / 20, true);
	amountOfTicks--;

	if (amountOfTicks > 0) {
		ChannelForceBuffTickEvent* cfbEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());
		cfbEvent->schedule(8000); // 8 Seconds.
	}
}
