/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DELEGATEFACTIONPOINTSCOMMAND_H_
#define DELEGATEFACTIONPOINTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/callbacks/DelegateSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "QueueCommand.h"

class DelegateFactionPointsCommand : public QueueCommand {
public:

	DelegateFactionPointsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	static int doDelegate(CreatureObject* creature, CreatureObject* targetPlayer, uint32 tipAmount) {
		Locker clocker(targetPlayer, creature);

		uint32 currentFaction = creature->getFaction();

		String faction;

		if (creature->isImperial()) {
			faction = "imperial";
		} else
			faction = "rebel";

		PlayerObject* delegator = creature->getPlayerObject();
		PlayerObject* targetPlayerObject = targetPlayer->getPlayerObject();

		int delegateRatioFrom = FactionManager::instance()->getRankDelegateRatioFrom(creature->getFactionRank());
		int delegateRatioTo = FactionManager::instance()->getRankDelegateRatioTo(creature->getFactionRank());

		int currentFactionPoints = delegator->getFactionStanding(faction);

		uint32 targetsRank = targetPlayer->getFactionRank();
		int targetsCap = FactionManager::instance()->getFactionPointsCap(targetsRank);
		int targetsCurrentPoints = targetPlayerObject->getFactionStanding(faction);

		float ratio = (float) delegateRatioFrom / (float)delegateRatioTo;

		uint32 charge = ceil((float)tipAmount * ratio);

		if (delegator->getFactionStanding(faction) < charge + 200) {
			StringIdChatParameter param("faction_recruiter", "not_enough_standing_spend");
			param.setDI(charge + 200);
			param.setTO(faction);
			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		if ((targetsCurrentPoints + tipAmount) > targetsCap) {
			creature->sendSystemMessage("That amount would exceed the player's current rank points limit.");
			return GENERALERROR;
		}

		targetPlayerObject->increaseFactionStanding(faction, tipAmount);
		delegator->decreaseFactionStanding(faction, charge);

		return SUCCESS;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		uint32 tipAmount = 0;

		if (target == 0)
			return INVALIDTARGET;

		//The player has SOMETHING targeted.
		//Lets first check if it's a player, cause if it is we can skip some stuff.
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		StringIdChatParameter params("@cmd_err:target_type_prose"); // Your target for %TO was invalid.
		params.setTO("Delegate Faction");

		if (object == NULL) {
			creature->sendSystemMessage(params);
			return INVALIDTARGET;
		}

		CreatureObject* targetCreature = dynamic_cast<CreatureObject*>(object.get());

		if (targetCreature == NULL) {
			creature->sendSystemMessage(params);
			return INVALIDTARGET;
		}

		Locker clocker(targetCreature, creature);

		ManagedReference<PlayerObject*> delegator = creature->getPlayerObject();
		PlayerObject* targetPlayerObject = targetCreature->getPlayerObject();

		if (targetPlayerObject == NULL) {
			creature->sendSystemMessage(params);
			return INVALIDTARGET;
		} else if (delegator == NULL)
			return GENERALERROR;

		uint64 delegatorID = creature->getObjectID();

		if (targetCreature->getObjectID() == delegatorID) {
			creature->sendSystemMessage("@error_message:target_self_disallowed"); // You cannot target yourself with this command.
			return INVALIDTARGET;
		}

		uint32 currentFaction = creature->getFaction();
		int delStatus = creature->getFactionStatus();

		if (currentFaction == 0 || delStatus != 2) {
			creature->sendSystemMessage("@base_player:must_be_declared"); // You must be declared to a faction before you may use that command.
			return GENERALERROR;
		}

		String faction;

		if (creature->isImperial()) {
			faction = "imperial";
		} else
			faction = "rebel";

		int delegateRatioFrom = FactionManager::instance()->getRankDelegateRatioFrom(creature->getFactionRank());
		int delegateRatioTo = FactionManager::instance()->getRankDelegateRatioTo(creature->getFactionRank());

		uint32 targetsRank = targetCreature->getFactionRank();
		int targetsCap = FactionManager::instance()->getFactionPointsCap(targetsRank);

		int currentFactionPoints = delegator->getFactionStanding(faction);
		int targetsCurrentPoints = targetPlayerObject->getFactionStanding(faction);

		if (targetsCurrentPoints == targetsCap) {
			creature->sendSystemMessage("That player has reached the faction points limit for their current rank.");
			return GENERALERROR;
		}

		if (currentFactionPoints < 200) {
			StringIdChatParameter param("faction_recruiter", "not_enough_standing_spend"); //"You do not have enough faction standing to spend. You must maintain at least %DI to remain part of the %TO faction."
			param.setDI(200);
			param.setTO(faction);
			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		if (!tokenizer.hasMoreTokens()) {
			ManagedReference<SuiTransferBox*> sui = new SuiTransferBox(creature, SuiWindowType::DELEGATE_TRANSFER);
			sui->setCallback(new DelegateSuiCallback(server->getZoneServer()));
			sui->setPromptTitle("@player_structure:select_amount"); //Select Amount
			sui->setPromptText("Current faction points:" + String::valueOf(delegator->getFactionStanding(faction)));
			sui->addFrom("Total amount", String::valueOf(currentFactionPoints), String::valueOf(currentFactionPoints), String::valueOf(delegateRatioFrom));
			sui->addTo("Delegate amount", "0", "0", String::valueOf(delegateRatioTo));
			sui->setUsingObject(targetCreature);
			sui->setForceCloseDistance(15.f);

			delegator->addSuiBox(sui);
			creature->sendMessage(sui->generateMessage());

			return SUCCESS;
		}

		tipAmount = (uint32) tokenizer.getIntToken();

		if (tipAmount == 0)
			return GENERALERROR;

		return doDelegate(creature, targetCreature, tipAmount);
	}

};

#endif //DELEGATEFACTIONPOINTSCOMMAND_H_
