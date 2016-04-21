#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/ChannelForceBuffTickEvent.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"
#include "templates/params/creature/CreatureAttribute.h"

void ChannelForceBuffImplementation::activate(bool applyModifiers) {
	if(creature.get() != NULL) {
		// Generic buff activate.
		BuffImplementation::activate(true);

		cfBuffEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());
		creature.get()->addPendingTask("channelForceTick", cfBuffEvent, 2000);
	}
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	if(creature.get() != NULL) {
		BuffImplementation::deactivate(true);
		creature.get()->removePendingTask("channelForceTick");
		cfBuffEvent = NULL;
	}
}

void ChannelForceBuffImplementation::doHamTick() {

	// Grab what the attribute modifiers have.
	VectorMap<byte, int>* attributeModifiers = getAttributeModifiers();

	// The time-related mod.
	float mod = getTimeLeft() / 8.f;

	for (int i = 0; i < attributeModifiers->size(); ++i) {
		byte attribute = attributeModifiers->elementAt(i).getKey();
		int modifier = attributeModifiers->elementAt(i).getValue();
		int healAmount = (int) MAX(0, -getBuffDuration() / 20);
		creature.get()->addMaxHAM(attribute, healAmount, true);

		if (getAttributeModifierValue(attribute) >= 0) {
			deactivate(true);
		}
	}

	Reference<ChannelForceBuffTickEvent*> ChannelCheck = creature.get()->getPendingTask("channelForceTick").castTo<ChannelForceBuffTickEvent*>();
	if (ChannelCheck != NULL) {
		ChannelCheck->reschedule(2000);
	}
}
