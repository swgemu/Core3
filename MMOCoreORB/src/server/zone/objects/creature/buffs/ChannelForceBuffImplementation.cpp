#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

void ChannelForceBuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();
}

void ChannelForceBuffImplementation::activate(bool applyModifiers) {
	if(creature.get() != NULL) {
		BuffImplementation::activate(false);
	}
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	if(creature.get() != NULL) {
		if (currentTick < amountOfTicks) {
			doHamTick();
			currentTick++;
			BuffImplementation::renew(buffDuration);
		} else {
			BuffImplementation::deactivate(false);
		}
	}
}

void ChannelForceBuffImplementation::doHamTick() {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	float tickAmnt = cfTick / amountOfTicks;

	creature.get()->addMaxHAM(CreatureAttribute::HEALTH, (int)tickAmnt, true);
	creature.get()->addMaxHAM(CreatureAttribute::ACTION, (int)tickAmnt, true);
	creature.get()->addMaxHAM(CreatureAttribute::MIND, (int)tickAmnt, true);
}
