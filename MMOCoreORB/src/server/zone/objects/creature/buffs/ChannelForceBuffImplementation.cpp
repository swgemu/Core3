#include "server/zone/objects/creature/buffs/ChannelForceBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/ChannelForceBuffTickEvent.h"

void ChannelForceBuffImplementation::initializeTransientMembers() {
	BuffImplementation::initializeTransientMembers();
	cfBuffEvent = nullptr;
}

void ChannelForceBuffImplementation::activate(bool applyModifiers) {
	BuffImplementation::activate(applyModifiers);
	activateRegenTick();
}

void ChannelForceBuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(removeModifiers);

	if (cfBuffEvent != nullptr) {
		cfBuffEvent->cancel();
		cfBuffEvent = nullptr;
	}
}

void ChannelForceBuffImplementation::activateRegenTick() {
	if (cfBuffEvent == nullptr)
		cfBuffEvent = new ChannelForceBuffTickEvent(_this.getReferenceUnsafeStaticCast());

	auto delay = FORCE_CHANNEL_TICK_DELAY_SECONDS * 1000;
	if (!cfBuffEvent->isScheduled())
		cfBuffEvent->schedule(delay);
	else
		cfBuffEvent->reschedule(delay);
}

void ChannelForceBuffImplementation::doHamTick() {
	ManagedReference<CreatureObject*> player = creature.get();

	if (player == nullptr)
		return;

	float timeLeft = getTimeLeft();
	// if timeLeft is negative or small, no reason to try anything here, deactivate() is about
	// to get called and will heal up everything left.
	if (timeLeft <= std::numeric_limits<float>::epsilon())
		return;

	// timeLeft is positive definite here (and must be greater than +epsilon), so use the ratio of
	// tick length to time left to calculate how much of the remaining modifer should be healed
	float healMod = FORCE_CHANNEL_TICK_SECONDS / timeLeft;

	Locker crossLock(player, _this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < attributeModifiers.size(); ++i) {
		byte attribute = attributeModifiers.elementAt(i).getKey();
		int modifier = attributeModifiers.elementAt(i).getValue();

		// this shouldn't really happen that much, so don't worry about dropping the element as we go
		if (modifier == 0)
			continue;

		// modifier should be negative, but even if it isn't negative, we can ensure that we
		// "undo" the effects of channel by taking the negative to calculate how much to modify
		// our attribute by this tick.
		int healAmount = -modifier * healMod; // this will round off, but it won't matter.

		// info(true) << "Attribute = " << attribute << " Modified = " << modifier << " healMod = " << healMod << " healAmount = " << healAmount;

		if (abs(healAmount) > abs(modifier)) // ensure we don't go into positive modifer territory
			healAmount = -modifier;

		int newMod = modifier + healAmount;

		// info(true) << "Updated healAmount = " << healAmount << " new Modifier = " << newMod << "\n\n\n";

		// we now add the healAmount to the modifier, which is necessarily the opposite sign of
		// modifier due to the definition.
		setAttributeModifier(attribute, newMod);

		// and finally apply that exact same amount to the HAM of the player
		player->addMaxHAM(attribute, healAmount, true);
	}

	// don't reschedule if tick length >= timeLeft (not mandatory, but useful)
	if (healMod < 1.f + std::numeric_limits<float>::epsilon())
		!cfBuffEvent ? activateRegenTick() : cfBuffEvent->reschedule(FORCE_CHANNEL_TICK_SECONDS * 1000);
}
