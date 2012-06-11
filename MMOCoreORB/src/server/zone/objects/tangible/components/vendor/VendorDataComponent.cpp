/*
 * VendorDataComponent.cpp
 *
 *  Created on: 5/29/2012
 *      Author: Kyle
 */

#include "VendorDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/auction/events/UpdateVendorTask.h"

VendorDataComponent::VendorDataComponent() {
	ownerId = 0;
	vendorId = 0;
	location = "";
	initialized = false;
	vendorSearchEnabled = false;
	disabled = false;
	registered = false;
	maintAmount = 0;
	awardUsageXP = 0;
	UID = "";
	addSerializableVariables();
}

void VendorDataComponent::addSerializableVariables() {
	addSerializableVariable("ownerId", &ownerId);
	addSerializableVariable("vendorId", &vendorId);
	addSerializableVariable("location", &location);
	addSerializableVariable("initialized", &initialized);
	addSerializableVariable("vendorSearchEnabled", &vendorSearchEnabled);
	addSerializableVariable("disabled", &disabled);
	addSerializableVariable("registered", &registered);
	addSerializableVariable("maintAmount", &maintAmount);
	addSerializableVariable("lastXpAward", &lastXpAward);
	addSerializableVariable("awardUsageXP", &awardUsageXP);
	addSerializableVariable("UID", &UID);
	addSerializableVariable("lastSuccessfulUpdate", &lastSuccessfulUpdate);
}

void VendorDataComponent::initializeTransientMembers() {

	vendor = cast<TangibleObject*>(Core::getObjectBroker()->lookUp(vendorId));

	if(vendor != NULL) {
		if (isInitialized()) {
			vendorCheckTask = new UpdateVendorTask(vendor);

			/// Schedule to run
			vendorCheckTask->schedule(1000);
		}
	}
}

void VendorDataComponent::notifyObjectDestroyingFromDatabase() {

	if(vendor == NULL)
		return;

	ManagedReference<CreatureObject*> player = cast<CreatureObject*>(vendor->getZoneServer()->getObject(ownerId));
	if(player == NULL)
		return;

	player->getPlayerObject()->removeVendor(vendor);
}

void VendorDataComponent::runVendorUpdate() {

	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(getOwnerId()));
	ManagedReference<PlayerManager*> playerManager = vendor->getZoneServer()->getPlayerManager();
	if (owner == NULL || !owner->isPlayerCreature() || playerManager == NULL) {
		return;
	}

	int now = time(0);
	int last = lastSuccessfulUpdate.getTime();
	float hoursSinceLastUpdate = now - last;
	hoursSinceLastUpdate /= 3600.f;

	/// Award hourly XP
	Locker locker(owner);
	playerManager->awardExperience(owner, "merchant", 150 * hoursSinceLastUpdate, false);

	playerManager->awardExperience(owner, "merchant", awardUsageXP * 50, false);
	awardUsageXP = 0;

	float skillReduction = 1;
	if(owner->hasSkill("crafting_merchant_sales_2"))
		skillReduction = .80f;
	if(owner->hasSkill("crafting_merchant_master"))
		skillReduction = .60f;

	/// Vendor salaries
	maintAmount -= ((15.f * skillReduction) * hoursSinceLastUpdate);

	/// 6 credits per hour to be registered
	if(registered)
		maintAmount -= (6 * hoursSinceLastUpdate);

	if(maintAmount < 0)
		vendor->setConditionDamage(-maintAmount, true);

	lastSuccessfulUpdate.updateToCurrentTime();
}
