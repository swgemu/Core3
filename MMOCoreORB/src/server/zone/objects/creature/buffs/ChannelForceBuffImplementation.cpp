

#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "ChannelForceBuffDurationEvent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

void ChannelForceBuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();
}

void ChannelForceBuffImplementation::activate(bool applyModifiers) {
	if(creature.get() != NULL) {
		Locker locker(creature.get());
		Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
		if (creature.get()->isIncapacitated() || creature.get()->isDead()) {
			// if the target is dead/incapped but the tick is happening before we de-active, then ignore the event
			return;
		}

		BuffImplementation::activate(false);
		cfBuffEvent = new ChannelForceBuffDurationEvent(creature.get(), _this.getReferenceUnsafeStaticCast());
		cfBuffEvent->execute();
	}
}

void ChannelForceBuffImplementation::deactivate() {
	if(creature.get() != NULL) {
		Locker locker(creature.get());
		Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());

		if (currentTick >= amountOfTicks) {
			BuffImplementation::deactivate(false);
		} else {
			doHamTick();
			currentTick++;
			cfBuffEvent->reschedule(10 * 1000);
		}
	}
}

void ChannelForceBuffImplementation::doHamTick() {
	Locker locker(creature.get());
	Locker lockerX(_this.getReferenceUnsafeStaticCast(),creature.get());
	if (!creature.get()->isIncapacitated() && !creature.get()->isDead()) {
		creature.get()->addMaxHAM(CreatureAttribute::HEALTH, cfTick, true);
		creature.get()->addMaxHAM(CreatureAttribute::ACTION, cfTick, true);
		creature.get()->addMaxHAM(CreatureAttribute::MIND, cfTick, true);
	}
}
