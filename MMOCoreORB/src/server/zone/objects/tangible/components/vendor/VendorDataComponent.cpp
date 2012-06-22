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
#include "server/zone/objects/player/sui/callbacks/VendorMaintSuiCallback.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
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
	adBarking = false;
	mail1Sent = false;
	mail2Sent = false;
	empty = true;
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
	addSerializableVariable("adBarking", &adBarking);
	addSerializableVariable("mail1Sent", &mail1Sent);
	addSerializableVariable("mail2Sent", &mail2Sent);
	addSerializableVariable("emptyTimer", &emptyTimer);
	addSerializableVariable("empty", &empty);
}

void VendorDataComponent::initializeTransientMembers() {

	vendor = cast<TangibleObject*>(Core::getObjectBroker()->lookUp(vendorId));

	if(vendor != NULL) {

		updateUID();

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

	if(vendorCheckTask == NULL)
		vendorCheckTask = new UpdateVendorTask(vendor);

	vendorCheckTask->reschedule(1000 * 60 * VENDORCHECKINTERVAL);

	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(getOwnerId()));
	ManagedReference<PlayerManager*> playerManager = vendor->getZoneServer()->getPlayerManager();
	if (owner == NULL || !owner->isPlayerCreature() || playerManager == NULL) {
		return;
	}

	int now = time(0);
	int last = lastSuccessfulUpdate.getTime();
	float hoursSinceLastUpdate = now - last;
	hoursSinceLastUpdate /= 3600.f;

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

	if(isEmpty()) {

		ChatManager* cman = vendor->getZoneServer()->getChatManager();

		String sender = vendor->getDisplayedName();
		UnicodeString subject("@auction:vendor_status_subject");


		if(!mail1Sent && time(0) - emptyTimer.getTime() > FIRSTWARNING) {
			StringIdChatParameter body("@auction:vendor_status_unaccessed");
			body.setTO(vendor->getDisplayedName());
			cman->sendMail(sender, subject, body, owner->getFirstName());
			mail1Sent = true;
		}

		if(!mail2Sent && time(0) - emptyTimer.getTime() > SECONDWARNING) {
			StringIdChatParameter body("@auction:vendor_status_endangered");
			body.setTO(vendor->getDisplayedName());
			cman->sendMail(sender, subject, body, owner->getFirstName());
			mail2Sent = true;
		}

		if(time(0) - emptyTimer.getTime() > DELETEWARNING || vendor->getConditionDamage() >= vendor->getMaxCondition()) {
			StringIdChatParameter body("@auction:vendor_status_deleted");
			cman->sendMail(sender, subject, body, owner->getFirstName());
			VendorManager::instance()->destroyVendor(vendor);
			vendorCheckTask->cancel();
		}

	} else {

		/// Award hourly XP
		Locker locker(owner);
		playerManager->awardExperience(owner, "merchant", 150 * hoursSinceLastUpdate, false);

		playerManager->awardExperience(owner, "merchant", awardUsageXP * 50, false);

	}

	awardUsageXP = 0;
	lastSuccessfulUpdate.updateToCurrentTime();
}

void VendorDataComponent::payMaintanence() {

	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(getOwnerId()));
	if(owner == NULL)
		return;

	ManagedReference<SuiInputBox*> input = new SuiInputBox(owner, SuiWindowType::STRUCTURE_VENDOR_PAY);
	input->setPromptTitle("@player_structure:pay_vendor_t"); //Add Militia Member
	input->setPromptText("@player_structure:pay_vendor_d");
	input->setUsingObject(vendor);
	input->setForceCloseDistance(5.f);
	input->setCallback(new VendorMaintSuiCallback(vendor->getZoneServer()));

	owner->getPlayerObject()->addSuiBox(input);
	owner->sendMessage(input->generateMessage());

}

void VendorDataComponent::handlePayMaintanence(int value) {

	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(getOwnerId()));
	if(owner == NULL)
		return;

	if(value > 100000) {
		owner->sendSystemMessage("@player_structure:vendor_maint_invalid");
		return;
	}

	if(value <= 0) {
		owner->sendSystemMessage("@player_structure:amt_greater_than_zero");
		return;
	}

	if(owner->getBankCredits() + owner->getCashCredits() > value) {
		maintAmount += value;
		if(owner->getBankCredits() > value) {
			owner->subtractBankCredits(value);
		} else {
			owner->subtractCashCredits(value - owner->getBankCredits());
			owner->subtractBankCredits(owner->getBankCredits());
		}
		owner->subtractBankCredits(value);
		StringIdChatParameter message("@player_structure:vendor_maint_accepted");
		message.setDI(maintAmount);
		owner->sendSystemMessage(message);
	} else {
		owner->sendSystemMessage("@player_structure:vendor_maint_denied");
	}
}

void VendorDataComponent::withdrawMaintanence() {

	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(getOwnerId()));
	if(owner == NULL)
		return;

	ManagedReference<SuiInputBox*> input = new SuiInputBox(owner, SuiWindowType::STRUCTURE_VENDOR_WITHDRAW);
	input->setPromptTitle("@player_structure:withdraw_vendor_t"); //Add Militia Member
	input->setPromptText("@player_structure:withdraw_vendor_d");
	input->setUsingObject(vendor);
	input->setForceCloseDistance(5.f);
	input->setCallback(new VendorMaintSuiCallback(vendor->getZoneServer()));

	owner->getPlayerObject()->addSuiBox(input);
	owner->sendMessage(input->generateMessage());

}

void VendorDataComponent::handleWithdrawMaintanence(int value) {
	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(getOwnerId()));
	if(owner == NULL)
		return;

	if(value > maintAmount) {
		owner->sendSystemMessage("@player_structure:vendor_withdraw_fail");
		return;
	}

	if(value <= 0) {
		owner->sendSystemMessage("@player_structure:amt_greater_than_zero");
		return;
	}

	maintAmount -= value;
	owner->addBankCredits(value, true);

	StringIdChatParameter message("@player_stucture:vendor_withdraw");
	message.setDI(maintAmount);
	owner->sendSystemMessage(message);
}
